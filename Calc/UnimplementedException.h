#pragma once
#include "CalcException.h"

namespace PR
{
	class UnimplementedException :
		public CalcException
	{
	public:
		UnimplementedException(const string &message);
		~UnimplementedException();
	};
}
