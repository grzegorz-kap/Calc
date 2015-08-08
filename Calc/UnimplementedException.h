#pragma once
#include "CalcException.h"

namespace KLab
{
	class UnimplementedException :
		public CalcException
	{
	public:
		UnimplementedException(const string &message);
		~UnimplementedException();
	};
}
