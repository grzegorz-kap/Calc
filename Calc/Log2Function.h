#pragma once
#include "Function.h"

namespace PR
{
	class Log2Function :
		public Function
	{
	public:
		Log2Function();
		~Log2Function();

		virtual shared_ptr<Data> run() override
		{
			return arguments[0]->log2();
		}
	};
}

