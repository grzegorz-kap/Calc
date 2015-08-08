#pragma once

#include "CalcException.h"

namespace KLab
{
	class OperatorException :
		public CalcException
	{
	public:
		OperatorException(const string &message, int position = 0);
		~OperatorException();
	};
}
