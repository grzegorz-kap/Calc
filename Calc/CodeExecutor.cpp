#include "stdafx.h"
#include "CodeExecutor.h"


namespace PR
{
	extern template class Matrix < double >;
	extern template class Matrix < hdouble >;
	extern template class ComplexNumber<double>;
	extern template class ComplexNumber<hdouble>;
	extern template class MatrixBuilder < double > ;
	extern template class MatrixBuilder < hdouble > ;

	CodeExecutor::CodeExecutor()
		:vars_ref(internal_vars)
	{
		_single_run = false;
		eval_flag = false;
		_file = "";
	}

	CodeExecutor::CodeExecutor(Variables &ref)
		:
		vars_ref(ref)
	{
		_single_run = false;
		eval_flag = false;
		_file = "";
	}

	CodeExecutor::CodeExecutor(const ExternalFunction &fun,const vector<shared_ptr<Data>> &args)
		:
		vars_ref(internal_vars),
		code(fun.getCode())
	{
		auto input = fun.getInput();
		int i = 0;
		_single_run = false;
		eval_flag = false;
		int N = input.size();
		_file = fun.getName();
		for (const shared_ptr<Data> &data : args)
		{
			if (i >= N)
				throw CalcException("Too many input parameters in function call (" + fun.getName() + ")");
			
			shared_ptr<Data> temp = data->_temp? data : data->copy();
			if (data->isOutput())
				TypePromotor::promote(temp, temp->max_type());
			vars_ref.set(input[i++],data);
		}
	}

	CodeExecutor::~CodeExecutor()
	{
	}

	void CodeExecutor::setInput(const string &in)
	{
		code.setInput(in);
	}

	void CodeExecutor::setInput(FileLoader &in)
	{
		_file = in.getFileName();
		code.setInput(in);
	}

	void CodeExecutor::set_stop_computing() 
	{ 
		stop_computing = true; 
	}

	void CodeExecutor::off_stop_computing()
	{ 
		stop_computing = false;
	}

	void CodeExecutor::start()
	{
		output_off_flag = false;
		while (!code.eof())
		{
			if (CodeExecutor::stop_computing)
				throw CalcException("Canceled!");
			ip = code.get();
			if (isKeyword(RETURN_KEYWORD))
				return;
			if (checkLoopsControl())
				continue;
			if (checkIF())
				continue;
			if (checkWhile())
				continue;
			if (checkFor())
				continue;
			try{
				run(false);
			}
			catch (const CalcException &ex)
			{
				if (ex.getLine() == 0)
					throwError(ex.getMessage());
				else
					throw ex;
			}
			code.inc();
		}
	}

	void CodeExecutor::start(const string &in)
	{
		CodeExecutor exec(vars_ref);
		exec.setInput(in);
		exec.start();
	}

	shared_ptr<Data> CodeExecutor::run(bool multi)
	{
		stack.clear();
		assignment.clear();

		for (i = ip->begin(); i != ip->end(); i++)
		{
			switch ((*i)->getClass())
			{
			case TOKEN_CLASS::NUMBER:
				stack.push_back(shared_ptr<Data>((*i)->evaluate()));
				break;
			case TOKEN_CLASS::OPERATOR:
				onOperator();
				break;
			case TOKEN_CLASS::ID:
				onID();
				break;
			case TOKEN_CLASS::MATRIX_START:
				stack.push_back(make_shared<Token>(MATRIX_START));
				break;
			case TOKEN_CLASS::VERSE_END:
				stack.push_back(make_shared<Token>(VERSE_END));
				break;
			case TOKEN_CLASS::MATRIX_END:
				onMatrixEnd();
				break;
			case TOKEN_CLASS::FUNCTON_ARGS_END:
				onFunctionArgs();
				break;
			case TOKEN_CLASS::FUNCTION:
				onFunction();
				break;
			case TOKEN_CLASS::ASSIGNMENT_TARGET:
				stack.push_back(*i);
				break;
			case TOKEN_CLASS::MATRIX_ALL:
			case TOKEN_CLASS::LAST_INDEX_OF:
				onMatrixAllOrLastInex();
				break;
			case TOKEN_CLASS::ASSIGNMENT:
				onAssignment();
				break;
			case TOKEN_CLASS::SHORT_CIRCUIT_END:
			case TOKEN_CLASS::SHORT_CIRCUIT_OR:
				onShortCircuitJumper();
				break;
			case TOKEN_CLASS::OUTPUT_OFF:
				output_off_flag = true;
				break;
			case TOKEN_CLASS::STRING:
				stack.push_back(*i);
				break;
			case TOKEN_CLASS::VARIABLES_MANAGEMENT:
				onVariablesManagement();
				break;
			default:
				throwError("Cannot execute this: '"+(*i)->getLexemeR()+"'");
			}
		}

		if (assignment_flag == false && !_single_id_flag && stack.size()==1)
			defaultAssignment();
		if (!_single_run && (stack.size() > 1 || !multi&&!_single_id_flag&&stack.size() == 1))
			throwError("Expression is incorrect.");
		if (!output_off_flag)
		{
			for (const auto & i : assignment)
			{
				SignalEmitter::get()->call(i.first->first, i.first->second);
			}
		}
		output_off_flag = false;
		assignment_flag = false;
		_single_id_flag = false;
		if (stack.size())
			return stack.back();
		else
			return make_shared<Data>();
	}
	
	vector<shared_ptr<Data>> CodeExecutor::run_single(const vector<shared_ptr<Token>> &onp,Variables &vars)
	{
		CodeExecutor exec(vars);
		exec._single_run = true;
		exec.assignment_flag = true;
		exec.output_off_flag = true;
		vector<vector<shared_ptr<Token>>> code = { onp };
		exec.ip = code.begin();
		exec.run();
		return exec.stack;
	}

	bool CodeExecutor::isMatrixEndOrColon(const shared_ptr<Token> &t)
	{
		return t->isToken(MATRIX_ALL) || t->isToken(LAST_INDEX_OF);
	}

	void CodeExecutor::onMatrixAllOrLastInex()
	{
		shared_ptr<Data> variable;
		try{
			variable = vars_ref.get((*i)->getLexemeR());
		}
		catch (const CalcException &ex)
		{
			throwError("Error evaulating 'end' or ':' matrix index - "+ ex.getMessageR());
		}

		int idx = (*i)->getParam();  // numer argumentu indeksowanie
		int num = (*i)->argumentsNum(); // rodzaj indeksowania

		if ((*i)->getClass() == MATRIX_ALL)
		{
			if (idx == 1 && num == 1)
				stack.push_back(variable->get_single_index());
			else if (idx == 1 && num == 2)
				stack.push_back(variable->get_rows_index());
			else if (idx == 2 && num == 2)
				stack.push_back(variable->get_cols_index());
			return;
		}

		if ((*i)->getClass() == LAST_INDEX_OF)
		{
			if (idx == 1 && num == 1)
				stack.push_back(*variable->get_rows() * variable->get_cols());
			else if (idx == 1 && num == 2)
				stack.push_back(variable->get_rows());
			else if (idx == 2 && num == 2)
				stack.push_back(variable->get_cols());
		}
	}

	void CodeExecutor::onOperator()
	{
		try{
			auto p = dynamic_pointer_cast<Operator>(*i);
			p->setArguments(stack);
			stack.push_back(p->evaluate());
			p->clearArguments();
		}
		catch (const CalcException &ex)
		{
			throwError(ex.getMessage());
		}
	}

	void CodeExecutor::onVariablesManagement()
	{
		string name = (*i)->getLexemeR();
		auto ii = find(TOKEN_CLASS::FUNCTON_ARGS_END, true);
		vector<shared_ptr<Data>> args(std::next(ii), stack.end());
		stack.erase(ii, stack.end());

		for (const auto &i : args)
		{
			if (i->_type != TYPE::STRING)
				throwError("Arguments of 'save' command must be string");
		}
		if (name == "load")
		{
			loadFromFile(args);
			return;
		}
		try{
			vars_ref.menage(name, FileLoader::getWorkingDirectory(), args);
		}
		catch (const CalcException &ex)
		{
			throwError(ex.getMessage(), args.size() ? args.front()->toString() : "");
		}
	}

	void CodeExecutor::loadFromFile(vector<shared_ptr<Data>> &args)
	{
		if (args.size() == 0)
			throwError("Too few arguments for 'load' command.");
		FileLoader file(args.front()->toString()+".klab");
		if (args.size() == 1)
		{
			CodeExecutor exec(vars_ref);
			exec.setInput(file);
			exec.start();
			return;
		}
		args.erase(args.begin());
		while (!file.eof())
		{
			string line = file.getLine();
			string name = line.substr(0, line.find("="));
			auto result = std::find_if(args.begin(), args.end(), [&name](shared_ptr<Data> &r){
				return r->toString() == name;
			});
			if (result != args.end())
			{
				start(line);
				args.erase(result);
			}
		}

	}

	void CodeExecutor::onShortCircuitJumper()
	{
		if (stack.size() == 0)
			throwError("Expression or statement is incomplete or incorrect.");
		
		if (!stack.back()->isScalar())
			throwError("Operands to the || and && operators must be convertible to logical scalar values");

		bool leftArgument = *stack.back() == true;
		TOKEN_CLASS _class = (*i)->getClass();
		if (leftArgument&&_class == SHORT_CIRCUIT_OR ||
			!leftArgument&&_class == SHORT_CIRCUIT_END)
			i = ip->begin() + 
				dynamic_pointer_cast<ShortCircuitJumper>(*i)
						->getJumpOn(_class) - 1;
	}

	bool CodeExecutor::isKeyword(TOKEN_CLASS _class)
	{
		return ip->size() == 1 && ip->at(0)->getClass() == _class;
	}

	vector<shared_ptr<Data>>::iterator CodeExecutor::find(TOKEN_CLASS _class, bool ex)
	{
		for (auto ii = stack.end() - 1; ii >= stack.begin(); ii--)
		{
			if ((*ii)->_type == TYPE::TOKEN && dynamic_cast<Token *>(ii->get())->getClass() == _class)
				return ii;
		}

		if (ex)
			throwError("Expected token not found!");
		else
			return stack.end();
	}

	void CodeExecutor::setIPTo(const vector<TOKEN_CLASS> &set, int balance)
	{
		if (set.size() == 0)
			return;
		while (1)
		{
			if (ip->size() == 1 && (balance==-2||balance == ip->at(0)->getKeywordBalance()) &&
				std::find(set.begin(), set.end(), ip->at(0)->getClass()) != set.end())
				return;
			next();
		}
	}

	void CodeExecutor::defaultAssignment()
	{
		auto target = make_unique<AssignmentSingle>();
		target->setTargetName("ans");
		stack.insert(stack.begin(), std::move(target));

		if (stack.size() >= 2 && stack.back()->_type == TYPE::OUTPUT)
			TypePromotor::convertTo(stack.back()->max_type(), stack.back(), stack.back());

		onAssignment();
	}

	void CodeExecutor::onAssignment()
	{
		if (stack.size() < 2)
			throwError("Too few arguments in data stack during assignment");
		if (eval_flag)
			throwError("Assignemnt unallowed here.");

		IAssignment * iassignment = stack.front()->cast_token()->castToAssignment();
		try{
			iassignment->doAssignment(vars_ref, std::next(stack.begin()), stack.end(), assignment);
		}
		catch (const CalcException &ex)
		{
			throwError(ex.getMessage());
		}
		stack.erase(stack.begin(), stack.begin() + 2);
		assignment_flag = true;
	}

	bool CodeExecutor::checkFor()
	{
		if (isKeyword(TOKEN_CLASS::FOR_KEYWORD))
		{
			onForKeyword();
			return true;
		}

		if (isKeyword(TOKEN_CLASS::END_FOR))
		{
			onForEndKeyword();
			return true;
		}
		return false;
	}

	void CodeExecutor::onForKeyword()
	{
		/* Utworzenie nowego interatora */
		for_iterators.push_back(ForIterator(vars_ref));
		ForIterator & _iterator = for_iterators.back();
		
		/* Ustawienie informacji o nazwie zmiennej bêd¹cej 
		   iteratorem oraz ustawienie zbioru wartoœci */
		auto _for = dynamic_pointer_cast<InstructionFor>(ip->front());
		_iterator.setName(_for->getLexeme());
		_iterator.setData(run_single(_for->getOnp(), vars_ref));

		/* Ustawienie adresu pocz¹tku cia³a pêtli oraz 
		   przejœcie na koniec pêtli */
		int balance = _for->getKeywordBalance();
		next();
		_iterator.setCodeBegin(code.getLP());
		setIPTo(FOR_FIND, balance);
	}

	void CodeExecutor::onForEndKeyword()
	{
		if (for_iterators.size() == 0)
			throwError("END-FOR found , but there is no for-iterators in memory!");
		ForIterator & _iterator = for_iterators.back();
		/* Je¿eli przeiterowano ca³y zestaw wartoœci */
		if (_iterator.end())
		{
			code.inc();
			for_iterators.pop_back();
		}
		else
		{
			/* Za³adowanie nastêpnej wartoœci do iteratora pêtli */
			_iterator.loadNext();
			/* Przejœcie do pocz¹tku pêtli */
			code.setIp(_iterator.getCodeBegin());
		}
	}

	bool CodeExecutor::checkLoopsControl()
	{
		if (isKeyword(CONTINUE_KEYWORD))
		{
			onContinueKeyword();
			return true;
		}
		if (isKeyword(BREAK_KEYWORD))
		{
			onBreakKeyword();
			return true;
		}
		return false;
	}

	void CodeExecutor::onContinueKeyword()
	{
		next();
		setIPTo(BRK_CONT_FIND, -2);
	}

	void CodeExecutor::onBreakKeyword()
	{
		next();
		setIPTo(BRK_CONT_FIND, -2);
		code.inc();
	}

	void CodeExecutor::onFunctionArgs()
	{
		/*
		Information about expected number of parameters returned from function
		*/
		if (i != ip->begin() && std::prev(i)->get()->getClass() == TOKEN_CLASS::ASSIGNMENT_TARGET)
		{
			stack.push_back(make_shared<Token>(TOKEN_CLASS::FUNCTON_ARGS_END, -1,
				std::prev(i)->get()->castToAssignment()->getTargetSize()));
		}
		else
			stack.push_back(make_shared<Token>(TOKEN_CLASS::FUNCTON_ARGS_END, -1, -1));
	}

	void CodeExecutor::onFunction()
	{
		const string &name = (*i)->getLexemeR();

		auto ii = find(TOKEN_CLASS::FUNCTON_ARGS_END, true);
		vector<shared_ptr<Data>> args(std::next(ii), stack.end());
		int num = (*ii)->cast_token()->getParam();
		stack.erase(ii, stack.end());

		shared_ptr<Data> var = vars_ref.get(name, false);
		if (var != nullptr)
		{
			onVariableFunction(args, var);
			return;
		}

		if (name == "eval")
		{
			onEval(args);
			return;
		}

		auto function = FunctionFactory::load_in(name);
		if (function != nullptr)
		{
			function->set(args, num > 0 ? num : 1);
			try{
				shared_ptr<Data> out = function->run();
				if (out->_type != TYPE::OUTPUT || out->cast_output()->getArgumentsNumber()>0)
					stack.push_back(out);
			}
			catch (const CalcException &ex)
			{
				throwError(ex.getMessage());
			}
		}
		else
			onExternalFunction(args, name);

	}

	void CodeExecutor::onEval(vector<shared_ptr<Data>> &args)
	{
		if (args.size() != 1)
			throwError("Wrong arguments number in 'eval' function");
		String *ptr = dynamic_cast<String*>(args[0].get());
		if (ptr == nullptr)
			throwError("String data type expected in 'eval' function");
		CodeExecutor exec(vars_ref);
		exec.eval_flag = true;
		exec.assignment_flag = true;
		exec.output_off_flag = true;
		exec.setInput(ptr->toString());
		exec.start();
		if (exec.stack.size() == 0)
			throwError("eval function must return value");
		stack.push_back(exec.stack.back());
	}

	void CodeExecutor::onVariableFunction(vector<shared_ptr<Data>> &args, shared_ptr<Data> &var)
	{
		int size = args.size();
		if (size > 2)
			throwError("Too many arguments while accessing variables cells");

		TYPE convertToType = var->_type == TYPE::STRING ? TYPE::M_DOUBLE : var->_type;

		try{
			for (int i = args.size() - 1; i >= 0; i--)
			{
				shared_ptr<Data> &ref = args[i];
				if (ref->_type != convertToType && !ref->isToken(TOKEN_CLASS::MATRIX_ALL) && !ref->isToken(TOKEN_CLASS::LAST_INDEX_OF))
					TypePromotor::convertTo(convertToType, ref, ref);
			}
			if (size == 2)
				stack.push_back(var->getAt(args[0], args[1]));
			else if (size == 1)
				stack.push_back(var->getAt(args[0]));
			else
				stack.push_back(var->getAt());
		}
		catch (const CalcException &ex)
		{
			throwError(ex.getMessage());
		}
	}

	void CodeExecutor::onExternalFunction(const vector<shared_ptr<Data>> &args, const string &name)
	{
		if (++recursions > recursion_limit)
			throw string("Error in '" + name + "'. Maximum recursion limit of " +
			std::to_string(recursion_limit) + " reached.");

		ExternalFunction function;
		try{
			function = FunctionFactory::load_external(name);
		}
		catch (const CalcException &ex)
		{
			throwError("Cannot load external function \""+name+"\":"+"\n"+ex.getFullMessage());
		}
		CodeExecutor exec(function, args);
		exec.start();
		recursions--;
		const vector<string>& output = function.getOutput();
		shared_ptr<Output> results = make_shared<Output>();
		results->_extern = true;
		for (const string &str : output)
		{
			auto result = exec.vars_ref.get(str);
			if (result == nullptr)
				break;
			results->add(result);
		}
		stack.push_back(results);
	}

	void CodeExecutor::onID()
	{
		try{
			if (ip->size() == 1)
			{
				assignment.push_back({ vars_ref.getIterator((*i)->getLexemeR()), false });
				_single_id_flag = true;
			}
			stack.push_back(vars_ref.get((*i)->getLexemeR()));
		}
		catch (const CalcException &ex)
		{
			if (!onScript())
				if ((*i)->getLexemeR() != "clc")
					throwError("Undefined variable or script '" + (*i)->getLexemeR() + "'.");
				else
					SignalEmitter::get()->call_sig_clear_screen();
		}
	}

	bool CodeExecutor::onScript()
	{
		if (ip->size() > 1)
			return false;

		FileLoader file((*i)->getLexeme() + ".m");
		if (!file.is_open())
			return false;

		CodeExecutor exec(vars_ref);
		exec.setInput(file);
		exec.start();
		assignment_flag = true;
		return true;
	}

	bool CodeExecutor::checkIF()
	{
		if (isKeyword(TOKEN_CLASS::IF_KEYWORD))
		{
			onIF();
			return true;
		}

		if (isKeyword(TOKEN_CLASS::ELSEIF_KEYWORD))
		{
			onElseIf();
			return true;
		}

		if (isKeyword(TOKEN_CLASS::END_IF))
		{
			code.inc();
			return true;
		}

		if (isKeyword(TOKEN_CLASS::ELSE_KEYWORD))
		{
			setIPTo(ELSE_FIND, ip->at(0)->getKeywordBalance());
			code.inc();
			return true;
		}

		return false;
	}

	void CodeExecutor::onElseIf()
	{
		int balance = ip->at(0)->getKeywordBalance();
		next();
		setIPTo(ELSEIF_FIND, balance);
		code.inc();
	}

	void CodeExecutor::onIF()
	{
		int balance = ip->at(0)->getKeywordBalance();
		next();
		assignment_flag = true;
		output_off_flag = true;
		if (*run() == false)
		{
			next();
			setIPTo(IF_FIND, balance);
			if (isKeyword(TOKEN_CLASS::ELSEIF_KEYWORD))
			{
				onIF();
				return;
			}
		}
		code.inc();
	}

	void CodeExecutor::onMatrixEnd()
	{
		vector<shared_ptr<Data>>::iterator ii;
		TYPE max_type = TYPE::TOKEN;


		for (ii = stack.end() - 1; ii >= stack.begin(); ii--)
		{
			auto _type = (*ii)->max_type();
			if (_type > max_type)
				max_type = _type;

			if ((*ii)->_type == TYPE::TOKEN)
			{
				Token *ptr = (*ii)->cast_token();
				if (ptr->getClass() == TOKEN_CLASS::MATRIX_START)
				{
					if (ptr->getEvType() > TYPE::TOKEN)
						max_type = ptr->getEvType();
					break;
				}
			}
		}

		max_type = max_type >= TYPE::DOUBLE ? IMatrixBuilder::TYPES.at(max_type) : TYPE::M_DOUBLE;

		if (ii < stack.begin())
			throwError("Matrix start not found");

		try{
			auto builder = MatrixBuilderFactory::get(max_type);
			for (auto k = std::next(ii); k != stack.end(); k++)
			{
				builder->add(*k);
			}
			builder->setAndCheckSize();
			stack.erase(ii, stack.end());
			stack.push_back(builder->getPtr());
		}
		catch (const CalcException &ex)
		{
			throwError(ex.getMessage());
		}
		
	}

	bool CodeExecutor::checkWhile()
	{
		if (isKeyword(TOKEN_CLASS::WHILE_KEYWORD))
		{
			onWHILE();
			return true;
		}
		if (isKeyword(TOKEN_CLASS::END_WHILE))
		{
			onWhileEnd();
			return true;
		}
		return false;
	}

	void CodeExecutor::onWhileEnd()
	{
		ip = code.get(conditions.back());
		assignment_flag = true;
		output_off_flag = true;
		if (*run() == false)
		{
			conditions.pop_back();
			code.inc();
		}
		else
		{
			code.setIp(conditions.back() + 1);
		}
	}

	void CodeExecutor::onWHILE()
	{
		int balance = ip->at(0)->getKeywordBalance();
		next();
		conditions.push_back(code.getLP());
		assignment_flag = true;
		output_off_flag = true;
		if (*run() == false)
		{
			next();
			setIPTo(WHILE_FIND, balance);
		}
		code.inc();
	}

	void CodeExecutor::next()
	{
		code.inc();
		ip = code.get(); 
	}

	void CodeExecutor::prev()
	{ 
		code.dec();	
		ip = code.get(); 
	}

	void CodeExecutor::throwError(const string &name,string src)
	{
		string tt = _file != "" ? _file + src : src;
		if (i != ip->end())
			throw CalcException(name, tt ,(*i)->getPosition(), (*i)->getLine());
		if (ip->size())
			throw CalcException(name, tt, ip->front()->getPosition(), ip->front()->getLine());
		throw CalcException(name);
	}

	decltype(AssignmentSubscripted::executor) AssignmentSubscripted::executor = CodeExecutor::run_single;

	const vector<TOKEN_CLASS> CodeExecutor::IF_FIND =
	{
		TOKEN_CLASS::END_IF,
		TOKEN_CLASS::ELSEIF_KEYWORD,
		TOKEN_CLASS::ELSE_KEYWORD
	};

	const vector<TOKEN_CLASS> CodeExecutor::ELSEIF_FIND =
	{
		TOKEN_CLASS::END_IF
	};

	const vector<TOKEN_CLASS> CodeExecutor::ELSE_FIND =
	{
		TOKEN_CLASS::END_IF
	};

	const vector<TOKEN_CLASS> CodeExecutor::WHILE_FIND =
	{
		TOKEN_CLASS::END_WHILE
	};

	const vector<TOKEN_CLASS> CodeExecutor::FOR_FIND =
	{
		TOKEN_CLASS::END_FOR
	};

	const vector<TOKEN_CLASS> CodeExecutor::BRK_CONT_FIND =
	{
		END_FOR, END_WHILE
	};

	bool CodeExecutor::stop_computing = false;

	int CodeExecutor::recursions = 0;
	int CodeExecutor::recursion_limit = 300;
}
