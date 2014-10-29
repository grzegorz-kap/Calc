#include "stdafx.h"
#include "UPlusOperator.h"


namespace PR
{
	UPlusOperator::UPlusOperator()
		:Operator("$+",30,1,EVAULATED::LEFT)
	{
	}


	UPlusOperator::~UPlusOperator()
	{
	}
}
