#include "stdafx.h"
#include "MatrixExponentiationOperator.h"


namespace PR
{
	MatrixExponentiationOperator::MatrixExponentiationOperator()
		:Operator("^",20,2,EVAULATED::RIGHT)
	{
	}


	MatrixExponentiationOperator::~MatrixExponentiationOperator()
	{
	}

}