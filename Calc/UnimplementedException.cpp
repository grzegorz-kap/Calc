#include "stdafx.h"
#include "UnimplementedException.h"

namespace KLab
{
	UnimplementedException::UnimplementedException(const string &message)
		:CalcException(message)
	{
	}

	UnimplementedException::~UnimplementedException()
	{
	}
}