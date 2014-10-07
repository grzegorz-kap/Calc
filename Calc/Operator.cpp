#include "stdafx.h"
#include "Operator.h"


namespace PR
{

	const vector<Operator> Operator::OPERATORS = {
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
	};


	Operator::Operator(const string &name, int priority, int arguments, EVAULATED ev)
		:
		priority(priority),
		arguments(arguments),
		ev(ev)
	{
		setLexeme(name);
		setType(TOKEN_CLASS::OPERATOR);
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

	int Operator::find(const string &name)
	{
		int N = Operator::OPERATORS.size();
		for (int i = 0; i < N; i++)
			if (Operator::OPERATORS[i].getLexemeR() == name)
				return i;
		return N;
	}

	const Operator & Operator::get(const string &name) 
	{
		auto n = Operator::find(name);
		if (n == Operator::OPERATORS.size())
			throw CalcException("Operator '" + name + "' not found!");
		return Operator::OPERATORS[n];
	}

}

