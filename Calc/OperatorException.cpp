#include "stdafx.h"
#include "OperatorException.h"

namespace KLab
{
	OperatorException::OperatorException(const string &message, int position)
		:CalcException(message, position)
	{
	}

	OperatorException::~OperatorException()
	{
	}
}