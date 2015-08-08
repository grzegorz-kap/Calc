#pragma once
#include "CalcException.h"

namespace PR
{
	class CastException :
		public CalcException
	{
	public:
		CastException(const string &message);
		~CastException();
	};
}
