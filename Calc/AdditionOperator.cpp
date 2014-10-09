#include "stdafx.h"
#include "AdditionOperator.h"


namespace PR
{
	AdditionOperator::AdditionOperator()
		:Operator("+",50,2,EVAULATED::RIGHT)
	{
	}


	AdditionOperator::~AdditionOperator()
	{
	}

}