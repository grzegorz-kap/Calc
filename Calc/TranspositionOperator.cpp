#include "stdafx.h"
#include "TranspositionOperator.h"


namespace PR
{
	TranspositionOperator::TranspositionOperator()
		:Operator(".'",20,1,EVAULATED::RIGHT)
	{
	}


	TranspositionOperator::~TranspositionOperator()
	{
	}
}
