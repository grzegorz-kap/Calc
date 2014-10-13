#include "stdafx.h"
#include "USubtractionOperator.h"


namespace PR
{
	USubtractionOperator::USubtractionOperator()
		:Operator("$-",30,1,EVAULATED::RIGHT)
	{
	}


	USubtractionOperator::~USubtractionOperator()
	{
	}
}
