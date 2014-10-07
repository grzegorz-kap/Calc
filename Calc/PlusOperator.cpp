#include "stdafx.h"
#include "PlusOperator.h"


namespace PR
{
	PlusOperator::PlusOperator()
		:Operator("+",50,2,EVAULATED::RIGHT)
	{
	}


	PlusOperator::~PlusOperator()
	{
	}

	shared_ptr<Data> PlusOperator::evaluate(STACK &stack)
	{
		if (stack.size() < arguments)
			throw OperatorException("Too few arguments in '+' operator");

		*stack.rbegin()[0] + stack.rbegin()[1];

	}

}