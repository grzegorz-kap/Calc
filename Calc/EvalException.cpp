#include "stdafx.h"
#include "EvalException.h"

namespace PR
{

	EvalException::EvalException(const string &message)
		:CalcException(message)
	{
	}


	EvalException::~EvalException()
	{
	}

}