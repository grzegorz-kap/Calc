#pragma once
#include "Function.h"

namespace PR
{
	class CosFun :
		public Function
	{
	public:
		CosFun();
		~CosFun();

		virtual shared_ptr<Data> run() override
		{
			return arguments[0]->cos();
		}
	};

}
