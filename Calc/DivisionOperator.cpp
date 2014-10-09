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
}
