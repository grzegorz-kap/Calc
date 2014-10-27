#pragma once
#include "Function.h"

namespace PR
{
	class SinFun
		: public Function
	{
	public:
		SinFun();
		~SinFun();

		virtual shared_ptr<Data> run() override
		{
			return arguments[0]->sin();
		}
	};
}

