#pragma once
#include "Function.h"

namespace PR
{
	class TanFun :
		public Function
	{
	public:
		TanFun();
		~TanFun();

		virtual shared_ptr<Data> run() override
		{
			return arguments[0]->tan();
		}
	};
}

