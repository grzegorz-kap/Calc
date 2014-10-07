#include "stdafx.h"
#include "OperatorException.h"

namespace PR
{

	OperatorException::OperatorException(const string &message, int position )
		:CalcException(message,position)
	{
	}


	OperatorException::~OperatorException()
	{
	}
}
