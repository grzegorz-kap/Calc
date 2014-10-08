#include "stdafx.h"
#include "CastException.h"


namespace PR
{
	CastException::CastException(const string &message)
		:CalcException(message)
	{
	}


	CastException::~CastException()
	{
	}

}