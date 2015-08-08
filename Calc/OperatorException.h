#pragma once

#include "CalcException.h"

namespace PR
{
	class OperatorException :
		public CalcException
	{
	public:
		OperatorException(const string &message, int position = 0);
		~OperatorException();
	};
}
