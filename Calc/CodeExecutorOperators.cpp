#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	void CodeExecutor::onOperator()
	{
		string op = (*i)->getLexeme();
		Operator oper = Operator::get(op);
		if (oper.getArguments() > stack.size())
		{
			throw CalcException("Too few operator arguments", (*i)->getPosition());
		}

		if (op == "+")
		{
			stack.push_back(shared_ptr<Data>(*pop() + pop()));
		}
		else if (op == "-")
		{
			stack.push_back(shared_ptr<Data>(*pop() - pop()));
		}
		else if (op == "*")
		{
			stack.push_back(shared_ptr<Data>(*pop() * pop()));
		}
		else if (op == "$-")
		{
			stack.push_back(shared_ptr<Data>(-*pop()));
		}
		else if (op == ".*")
		{
			stack.push_back(shared_ptr<Data>(pop()->mult_t(pop())));
		}
		else if (op == "./")
		{
			stack.push_back(shared_ptr<Data>(pop()->div_t(pop())));
		}
		else if (op == "/")
			stack.push_back(shared_ptr<Data>(*pop() / pop()));
		else if (op == "'")
			stack.push_back(MatrixTransposer::transpose(pop()));
	}
}