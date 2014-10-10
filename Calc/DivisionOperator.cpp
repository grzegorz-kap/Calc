#include "stdafx.h"
#include "DivisionOperator.h"


namespace PR
{
	DivisionOperator::DivisionOperator()
		:Operator("/",40,2,EVAULATED::RIGHT)
	{
	}


	DivisionOperator::~DivisionOperator()
	{
	}

	shared_ptr<Data> DivisionOperator::evaluate()
	{
		return *arguments[0] / arguments[1];
	}
}
