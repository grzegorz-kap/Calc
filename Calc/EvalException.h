#pragma once
#include "CalcException.h"
namespace PR
{
	class EvalException :
		public CalcException
	{
	public:
		EvalException(const string &message);
		~EvalException();
	};

}
