#include "stdafx.h"
#include "ExponentiationOperator.h"


namespace PR
{
	ExponentiationOperator::ExponentiationOperator()
		:Operator(".^",20,2,EVAULATED::RIGHT)
	{
	}


	ExponentiationOperator::~ExponentiationOperator()
	{
	}
}
