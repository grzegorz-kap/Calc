#include "stdafx.h"
#include "UnimplementedException.h"

namespace PR
{
	UnimplementedException::UnimplementedException(const string &message)
		:CalcException(message)
	{
	}

	UnimplementedException::~UnimplementedException()
	{
	}
}