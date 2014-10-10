#include "stdafx.h"
#include "SubtractionOperator.h"


namespace PR
{
	SubtractionOperator::SubtractionOperator()
		:Operator("-", 50, 2, EVAULATED::RIGHT)
	{
	}


	SubtractionOperator::~SubtractionOperator()
	{
	}

	shared_ptr<Data> SubtractionOperator::evaluate()
	{
		return *arguments[0] - arguments[1];
	}

}