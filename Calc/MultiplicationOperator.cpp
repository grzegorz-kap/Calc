#include "stdafx.h"
#include "MultiplicationOperator.h"


namespace PR
{
	MultiplicationOperator::MultiplicationOperator()
		:Operator("*",40,2,EVAULATED::RIGHT)
	{
	}


	MultiplicationOperator::~MultiplicationOperator()
	{
	}

}