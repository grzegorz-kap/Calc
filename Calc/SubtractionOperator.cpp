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

}