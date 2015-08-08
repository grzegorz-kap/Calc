#include "stdafx.h"
#include "CastException.h"

namespace KLab
{
	CastException::CastException(const string &message)
		:CalcException(message)
	{
	}

	CastException::~CastException()
	{
	}
}