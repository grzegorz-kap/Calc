#include "stdafx.h"
#include "CodeExecutor.h"


namespace PR
{
	

	CodeExecutor::CodeExecutor()
		:vars_ref(internal_vars)
	{
	}

	CodeExecutor::CodeExecutor(variables &ref)
		:
		vars_ref(ref)
	{
	}


	CodeExecutor::CodeExecutor(const ExternalFunction &fun,const vector<shared_ptr<Data>> &args)
		:
		vars_ref(internal_vars),
		code(fun.getCode())
	{
		auto input = fun.getInput();
		int i = 0;
		int N = input.size();
		for (const shared_ptr<Data> &data : args)
		{
			if (i >= N)
				throw CalcException("Too many input parameters in function call (" + fun.getName() + ")");
			vars_ref[input[i++]] = data;
		}
	}

	CodeExecutor::~CodeExecutor()
	{
	}

	void CodeExecutor::start()
	{
		output_off_flag = false;
		while (!code.eof())
		{
			ip = code.get();
			if (checkIF())
				continue;
			if (checkWhile())
				continue;
			run();
			code.inc();
		}
	}

	void CodeExecutor::setIPTo(const vector<TOKEN_CLASS> &set,int balance)
	{
		if (set.size() == 0)
			return;
		while (1)
		{
			if ( ip->size()==1 && balance == ip->at(0)->getKeywordBalance() &&
				std::find(set.begin(), set.end(), ip->at(0)->getClass()) != set.end())
				return;
			next();
		}
	}

	shared_ptr<Data> CodeExecutor::run()
	{
		stack.clear();
		assignment_flag = false;
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
				stack.push_back(make_shared<Token>(FUNCTON_ARGS_END));
				break;
			case TOKEN_CLASS::FUNCTION:
				onFunction();
				break;
			case TOKEN_CLASS::ASSIGNMENT_TARGET:
				stack.push_back(make_shared<Assignment>(*(*i)->castToAssignment()));
				break;
			case TOKEN_CLASS::ASSIGNMENT:
				onAssignment();
				break;
			case TOKEN_CLASS::ID:
				stack.push_back(vars_ref[(*i)->getLexemeR()]);
				break;
			case TOKEN_CLASS::OUTPUT_OFF:
				output_off_flag = true;
				break;
			default:
				throw CalcException("!");
			}
		}

		if (assignment_flag == false)
			defaultAssignment();

		output_off_flag = false;
		if (stack.size())
			return stack.back();
		else
			return make_shared<Data>();
	}

	void CodeExecutor::defaultAssignment()
	{

	}

	void CodeExecutor::onAssignment()
	{
		if (stack.size() < 2)
			throw CalcException("!");

		auto &target = std::dynamic_pointer_cast<Assignment>(*stack.begin())->getTarget();
		auto data = std::next(stack.begin());
		
		if ((*data)->isOutput())
		{
			auto source = std::dynamic_pointer_cast<Output>(*data)->getOutput();
			auto oo = source.begin();
			for (auto ii = target.begin(); ii != target.end(); ii++)
			{
				if (oo == source.end())
					throw CalcException("!");
				assignment.push_back(vars_ref.insert({ (*ii)->getLexemeR(), *oo }));
				oo++;
			}
		}
		else
		{
			assignment.push_back(vars_ref.insert({ target[0]->getLexemeR(), *data }));
		}
		stack.erase(stack.begin(), stack.begin() + 2);
		assignment_flag = true;
	}

	void CodeExecutor::onOperator()
	{
		auto p = dynamic_cast<Operator *>(i->get());
		p->setArguments(stack);
 		stack.push_back(shared_ptr<Data>(p->evaluate()));
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
			throw CalcException("Expected token not found!");
		else
			return stack.end();
	}
}
