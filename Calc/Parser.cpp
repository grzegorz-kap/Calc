#include "stdafx.h"
#include "Parser.h"



namespace PR
{
	Parser::Parser()
	{

	}

	Parser::Parser(LexicalAnalyzer &lex)
	{
		tokens = lex.getTokens();
		iter = tokens.begin();
	}

	Parser::~Parser()
	{
		
	}

	void Parser::setInput(LexicalAnalyzer &lex)
	{
		tokens = lex.getTokens();
		iter = tokens.begin();
	}

	bool Parser::parse()
	{
		stack.clear();
		onp.clear();
		_function_names.clear();
		_function_args.clear();
		_function_onp_addr.clear();
		stop = false;

		for (; !stop && iter != tokens.end(); ++iter)
		{
			i = std::move(*iter);
			switch (i->getClass())
			{
			case TOKEN_CLASS::NUMBER:
				onNumber();
				break;
			case TOKEN_CLASS::ID:
				onID();
				break;
			case TOKEN_CLASS::COMMA:
				onComma();
				break;
			case TOKEN_CLASS::OPEN_PARENTHESIS:
				onOpenParenthesis();
				break;
			case TOKEN_CLASS::FUNCTION:
				onFunction();
				break;
			case TOKEN_CLASS::SEMICOLON:
				onSemicolon();
				break;
			case TOKEN_CLASS::OPERATOR:
				onOperator();
				break;
			case TOKEN_CLASS::CLOSE_PARENTHESIS:
				onCloseParenthesis();
				break;
			case TOKEN_CLASS::NEW_LINE:
				onNewLine();
				break;
			case TOKEN_CLASS::MATRIX_START:
				onMatrixStart();
				break;
			case TOKEN_CLASS::MATRIX_END:
				onMatrixEnd();
				break;
			case TOKEN_CLASS::COLON:
				onColon();
				break;
			case TOKEN_CLASS::MATRIX_ALL:
			case TOKEN_CLASS::LAST_INDEX_OF:
				onMatrixAll();
				break;
			case TOKEN_CLASS::FOR_KEYWORD:
				onKeywordFOR();
				stop = true;
				break;
			case TOKEN_CLASS::STRING:
				onp.push_back(std::move(i));
				break;
			case TOKEN_CLASS::KEY_WORD:
			case TOKEN_CLASS::IF_KEYWORD:
			case TOKEN_CLASS::ELSE_KEYWORD:
			case TOKEN_CLASS::ELSEIF_KEYWORD:
			case TOKEN_CLASS::END_IF:
			case TOKEN_CLASS::END_WHILE:
			case TOKEN_CLASS::WHILE_KEYWORD:
			case TOKEN_CLASS::FUNCTION_KEYWORD:
			case TOKEN_CLASS::END_FUNCTION:
			case TOKEN_CLASS::CONTINUE_KEYWORD:
			case TOKEN_CLASS::BREAK_KEYWORD:
			case TOKEN_CLASS::RETURN_KEYWORD:
			case TOKEN_CLASS::END_FOR:
				if (onp.size() == 0 && stack.size() == 0)
					onp.push_back(make_unique<Token>(*i));
				stop = true;
				break;
			default:
				throw CalcException("Parser. Unexpected symbol: '" + i->getLexemeR() + "'.", i->getPosition());
				break;
			}
		}
		stackToOnpAll();
		computeTreeLevels();
		changeIfAssignment();
		computeShortCircuitJumps(onp);
		return iter != tokens.end();
	}

	void Parser::onComma()
	{
		if (i->getMode() == PARSE_MODE::NORMAL||i->getMode()==PARSE_MODE::KEYWORD)
			stop = true;
		else
		{
			TOKEN_CLASS type = i->getMode() == PARSE_MODE::FUNCTION ? TOKEN_CLASS::OPEN_PARENTHESIS : TOKEN_CLASS::MATRIX_START;
			bool flag = false;
			for (int i = stack.size()-1; i >= 0; i--)
			{
				if (stack[i]->getClass() == type)
				{
					flag = true;
					break;
				}
				else
					stackToOnp();
			}
			if (!flag)
				throw CalcException("Unbalanced parenthesis!");
		}
		if (i->getMode() == PARSE_MODE::FUNCTION)
			_function_args.back()++;
	}

	void Parser::onFunction()
	{
		onp.push_back(make_shared<Token>(TOKEN_CLASS::FUNCTON_ARGS_END));
		stack.push_back(make_shared<Token>(*i));
		_function_names.push_back(i->getLexemeR());
		_function_args.push_back(1);
		_function_onp_addr.push_back(vector<int>());
	}

	void Parser::onID()
	{		
		if (whatNext() == TOKEN_CLASS::OPEN_PARENTHESIS)
		{
			Token token = *i;
			token.set_class(TOKEN_CLASS::FUNCTION);
			stack.push_back(make_shared<Token>(token));
			onp.push_back(make_shared<Token>(TOKEN_CLASS::FUNCTON_ARGS_END));
			_function_names.push_back(token.getLexemeR());
			_function_args.push_back(1);
			_function_onp_addr.push_back(vector<int>());
			if (token.getLexemeR() == "mpf_float")
			{
				_ev_type_mode.push_back(TYPE::R_DOUBLE);
				_ev_type_balance.push_back(0);
			}
			else if (token.getLexemeR() == "double")
			{
				_ev_type_balance.push_back(0);
				_ev_type_mode.push_back(TYPE::DOUBLE);
			}
		}
		else
			onp.push_back(make_shared<Token>(*i));
	}

	void Parser::onNewLine()
	{
		if (i->getMode() == PARSE_MODE::MATRIX)
			onSemicolon();
		else if (onp.size())
			stop = true;
	}

	void Parser::onNumber()
	{
		if (_ev_type_mode.size())
			i->setEvType(_ev_type_mode.back());
		onp.push_back(std::move(i));
	}

	void Parser::stackToOnpUntilToken(TOKEN_CLASS type,bool remove)
	{
		bool flag = true;
		for (int i = stack.size() - 1; i >= 0; i--)
		{
			if (stack[i]->getClass() == type)
			{
				flag = false;
				if (remove)
					stack.pop_back();
				break;
			}
			else
				stackToOnp();
		}
		if (flag)
			throw CalcException("Unbalanced or unexpected parenthesis or bracket.");
	}

	void Parser::onOpenParenthesis()
	{
		if (_ev_type_balance.size())
			_ev_type_balance.back()++;

		stack.push_back(make_unique<Token>(*i));
	}

	void Parser::onCloseParenthesis()
	{
		if (_ev_type_balance.size() && _ev_type_balance.back()-- == 1)
		{
			_ev_type_balance.pop_back();
			_ev_type_mode.pop_back();
		}

		stackToOnpUntilToken(TOKEN_CLASS::OPEN_PARENTHESIS);
		if (stackBack() == TOKEN_CLASS::FUNCTION)
		{
			_function_names.pop_back();
			stack.back()->argumentsNum(_function_args.back());

			for (int i : _function_onp_addr.back())
			{
				if (i < onp.size())
					onp[i]->argumentsNum(_function_args.back());
			}

			_function_args.pop_back();
			stackToOnp();
		}
	}

	void Parser::onOperator()
	{ 
		Operator *o1 = i->castToOperator();
		while (stackBack() == TOKEN_CLASS::OPERATOR )
		{
			Operator *o2 = stack.back()->castToOperator();
			if (o1->getLexemeR() == ":" && o2->getLexemeR() == ":")
			{
				stack.pop_back();
				stack.push_back(make_unique<Colon3Operator>());
				return;
			}
			if (*o1 < *o2)
				stackToOnp();
			else
				break;
		}
		onShortCircuitOperator();
		stack.push_back(std::move(i));
	}

	void Parser::onShortCircuitOperator()
	{
		if (i->getLexemeR() == "&&")
			onp.push_back(make_unique<ShortCircuitJumper>(TOKEN_CLASS::SHORT_CIRCUIT_END));
		else if (i->getLexemeR() == "||")
			onp.push_back(make_unique<ShortCircuitJumper>(TOKEN_CLASS::SHORT_CIRCUIT_OR));
	}

	void Parser::computeShortCircuitJumps( vector<shared_ptr<Token>> &onp)
	{
		for (auto iter = onp.begin(); iter != onp.end(); ++iter)
		{
			auto &ptr = *iter;
			TOKEN_CLASS _class = ptr->getClass();
			if (_class == TOKEN_CLASS::SHORT_CIRCUIT_END || _class == TOKEN_CLASS::SHORT_CIRCUIT_OR)
			{
				int _level = ptr->getTreeLevel();
				auto result = std::find_if(iter + 1, onp.end(), [&_level, &_class](const shared_ptr<Token> &token){
					bool lvl = _level == token->getTreeLevel();
					bool end = TOKEN_CLASS::SHORT_CIRCUIT_END == _class && token->getLexemeR() == "&&";
					bool or = TOKEN_CLASS::SHORT_CIRCUIT_OR == _class && token->getLexemeR() == "||";
					return lvl && (end || or);
				});
				int idx = std::distance(onp.begin(), result);
				if (_class == TOKEN_CLASS::SHORT_CIRCUIT_END)
					dynamic_cast<ShortCircuitJumper *>(ptr.get())->setJumpOnFalse(idx + 1);
				else if (_class == TOKEN_CLASS::SHORT_CIRCUIT_OR)
					dynamic_cast<ShortCircuitJumper *>(ptr.get())->setJumpOnTrue(idx + 1);
			}
		}
	}

	void Parser::computeTreeLevels()
	{
		int main = 0;
		vector<int> funs;
		vector<int> mtrx;
		vector<int> mains;
		for (const auto &t : onp)
		{
			int balance = 0;
			switch (t->getClass())
			{
			case TOKEN_CLASS::ID:
			case TOKEN_CLASS::NUMBER:
			case TOKEN_CLASS::STRING:
				balance = 1; break;
			case TOKEN_CLASS::FUNCTON_ARGS_END:
				funs.push_back(0); break;
			case TOKEN_CLASS::MATRIX_START:
				mtrx.push_back(0); break;
			case TOKEN_CLASS::OPERATOR:
				balance = -t->castToOperator()->getArgumentsNum() + 1; break;
			case TOKEN_CLASS::MATRIX_END:
				balance = -mtrx.back() + 1; mtrx.pop_back(); break;
			case TOKEN_CLASS::FUNCTION:
				balance = -funs.back() + 1; funs.pop_back(); break;
			}
			main += balance;
			if (funs.size()) funs.back() += balance;
			if (mtrx.size()) mtrx.back() += balance;
			t->setTreeLevel(main);
			mains.push_back(main);
		}
	}

	void Parser::onMatrixStart()
	{
		stack.push_back(make_unique<Token>(*i));
		onp.push_back(make_unique<Token>(*i));
		if (_ev_type_mode.size())
			onp.back()->setEvType(_ev_type_mode.back());
	}

	void Parser::onMatrixAll()
	{
		if (_function_names.size() == 0||_function_args.size()==0)
			throw CalcException("Unexpected end keyword or : operator",i->getPosition());
		onp.push_back(make_shared<Token>(*i));
		onp.back()->setLexeme(_function_names.back());
		onp.back()->setParam(_function_args.back());
		_function_onp_addr.back().push_back(onp.size()-1);
	}

	void Parser::onMatrixEnd()
	{
		stackToOnpUntilToken(TOKEN_CLASS::MATRIX_START);
		if (i->getMode()!=PARSE_MODE::MATRIX)
			onp.push_back(make_unique<Token>(TOKEN_CLASS::VERSE_END));
		onp.push_back(make_unique<Token>(*i));
	}

	void Parser::onColon()
	{
		i = make_unique<Colon2Operator>();
		onOperator();
	}

	void Parser::onSemicolon()
	{
		switch (i->getMode())
		{
		case PARSE_MODE::MATRIX:
			stackToOnpUntilToken(TOKEN_CLASS::MATRIX_START,false);
			onp.push_back(make_unique<Token>(TOKEN_CLASS::VERSE_END));
			break;
		case PARSE_MODE::NORMAL:
		case PARSE_MODE::KEYWORD:
			stop = true;
			stackToOnpAll();
			onp.push_back(make_shared<Token>(TOKEN_CLASS::OUTPUT_OFF));
			break;
		}
	}

	TOKEN_CLASS Parser::stackBack() const
	{
		if (stack.size() != 0)
			return stack.back()->getClass();
		else
			return TOKEN_CLASS::NONE;
	}

	TOKEN_CLASS Parser::onpBack() const
	{
		if (onp.size() != 0)
			return onp.back()->getClass();
		else
			return TOKEN_CLASS::NONE;
	}

	void Parser::stackToOnpAll()
	{
		for (int i = stack.size() - 1; i >= 0; i--)
		{
			TOKEN_CLASS _type = stack[i]->getClass();
			if (_type != TOKEN_CLASS::OPERATOR)
				throw CalcException("Unexpected symbol!", stack[i]->getPosition());
			onp.push_back(std::move(stack[i]));
		}
		stack.clear();
	}
	
	void Parser::stackToOnp()
	{
		onp.push_back(std::move(stack.back()));
		if (_function_args.size())
			onp.back()->argumentsNum(_function_args.back());
		stack.pop_back();
	}

	void Parser::iterBack()
	{
		if (tokens.begin() != iter)
			iter--;
	}

	void Parser::changeIfAssignment()
	{
		if (onp.size() < 3)
			return;

		bool find = false;
		if (onp.back()->getLexemeR() == "=")
		{
			find = true;
			onp.back()->set_class(TOKEN_CLASS::ASSIGNMENT);
		}

		if (!find && onp.back()->getClass() == TOKEN_CLASS::OUTPUT_OFF && onp.rbegin()[1]->getLexemeR() == "=")
		{
			find = true;
			onp.rbegin()[1]->set_class(TOKEN_CLASS::ASSIGNMENT);
		}

		if (!find)
			return;

		unique_ptr<IAssignment> iAssignment(AssignmentFactory::get(onp.front()->getClass()));

		auto start = onp.begin();
		auto end = onp.end();
		iAssignment->loadTarget(start, end);
		if (iAssignment->_assignment_type == ASSIGNMENT_TYPE::SUBSCRIPTED)
		{
			auto ptr = dynamic_cast<AssignmentSubscripted*>(iAssignment.get());
			computeShortCircuitJumps(ptr->getOnpRef());
		}
		onp.erase(onp.begin(), start);
		onp.insert(onp.begin(), std::move(iAssignment));
	}

	void Parser::onKeywordFOR()
	{
		unique_ptr<InstructionFor> _for = make_unique<InstructionFor>(*i);
		iter++;

		if (iter == tokens.end())
			throw CalcException("Unexpected end of code", i->getPosition());

		parse();

		if (onp.size() < 3)
			throw CalcException("Error parsing 'for' keyword", i->getPosition());

		AssignmentSingle * assignment = dynamic_cast<AssignmentSingle *>(onp.front().get());
		if (assignment == nullptr)
			throw CalcException("Error in for instruction,single assignment not found!");
		_for->setName(assignment->getLexeme());
		onp.erase(onp.begin());

		if (onp.back()->getClass() == TOKEN_CLASS::OUTPUT_OFF)
			onp.pop_back();
		if (onp.back()->getClass() == TOKEN_CLASS::ASSIGNMENT)
			onp.pop_back();

		if (onp.size() == 0)
			throw CalcException("Error parsing 'for' keyword", i->getPosition());

		_for->setOnp(std::move(onp));
		onp.push_back(std::move(_for));
		iterBack();
	}

	TOKEN_CLASS Parser::whatNext()
	{
		if (iter + 1 == tokens.end())
			return TOKEN_CLASS::NONE;
		return (*(iter + 1))->getClass();
	}

	vector<shared_ptr<Token>> & Parser::getInstruction()
	{ 
		return onp; 
	}
}