#include "stdafx.h"
#include "EvalException.h"

namespace KLab
{
	EvalException::EvalException(const string &message, int pos)
		:CalcException(message, pos)
	{
	}

	EvalException::~EvalException()
	{
	}
}