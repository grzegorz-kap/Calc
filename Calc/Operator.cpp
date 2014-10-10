#include "stdafx.h"
#include "Operator.h"


namespace PR
{

	/*const vector<Operator> Operator::OPERATORS = {
		Operator(".'", 20, 1, EVAULATED::RIGHT),
		Operator(".^", 20, 2, EVAULATED::RIGHT),
		Operator(".*", 40, 2, EVAULATED::RIGHT),
		Operator("./", 40, 2, EVAULATED::RIGHT),
		Operator("\\.", 40, 2, EVAULATED::RIGHT),
		Operator("*", 40, 2, EVAULATED::RIGHT),
		Operator("/", 40, 2, EVAULATED::RIGHT),
		Operator("\\", 40, 2, EVAULATED::RIGHT),
		Operator("<=", 70, 2, EVAULATED::RIGHT),
		Operator(">=", 70, 2, EVAULATED::RIGHT),
		Operator("==", 70, 2, EVAULATED::RIGHT),
		Operator("~=", 70, 2, EVAULATED::RIGHT),
		Operator("<", 70, 2, EVAULATED::RIGHT),
		Operator(">", 70, 2, EVAULATED::RIGHT),
		Operator("'", 20, 1, EVAULATED::RIGHT),
		Operator("^", 20, 2, EVAULATED::RIGHT),
		Operator("+", 50, 2, EVAULATED::RIGHT),
		Operator("-", 50, 2, EVAULATED::RIGHT),
		Operator(":", 60, 2, EVAULATED::LEFT),
		Operator("=", 100, 2, EVAULATED::LEFT),
		Operator("$+", 30, 1, EVAULATED::RIGHT),
		Operator("$-", 30, 1, EVAULATED::RIGHT),
		Operator("~", 30, 1, EVAULATED::RIGHT),
	};*/


	Operator::Operator(const string &name, int priority, int arguments, EVAULATED ev)
		:
		priority(priority),
		argumentsNum(arguments),
		ev(ev)
	{
		setLexeme(name);
		set_class(TOKEN_CLASS::OPERATOR);
	}


	Operator::~Operator()
	{
	}

	bool Operator::operator<(const Operator &b) const
	{
		if (priority > b.priority || ev == EVAULATED::RIGHT && priority == b.priority)
			return true;
		else
			return false;
	}

	void Operator::setArguments(vector<shared_ptr<Data>> &stack)
	{
		if (stack.size() < argumentsNum)
			throw EvalException("Too few arguments for operator: " + getLexemeR());

		arguments.resize(argumentsNum);

		auto iter = stack.rbegin();
		int k = argumentsNum - 1;
		for (int i = 0; i < argumentsNum; i++)
		{
			arguments[i] = iter[k--];
		}

		stack.erase(stack.begin() + stack.size() - argumentsNum, stack.end());
	}
}

