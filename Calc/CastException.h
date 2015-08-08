#pragma once
#include "CalcException.h"

namespace KLab
{
	class CastException :
		public CalcException
	{
	public:
		CastException(const string &message);
		~CastException();
	};
}
