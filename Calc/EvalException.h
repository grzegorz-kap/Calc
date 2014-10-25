#pragma once
#include "CalcException.h"
namespace PR
{
	class EvalException :
		public CalcException
	{
	public:
		EvalException(const string &message,int pos=-1);
		~EvalException();
	};

}
