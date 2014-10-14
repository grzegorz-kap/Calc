#include "stdafx.h"
#include "EqOperator.h"


namespace PR
{
	EqOperator::EqOperator()
		:Operator("==",70,2,EVAULATED::RIGHT)
	{
	}


	EqOperator::~EqOperator()
	{
	}
}
