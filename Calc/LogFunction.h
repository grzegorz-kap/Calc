#pragma once
#include "Function.h"

namespace PR
{
	class LogFunction :
		public Function
	{
	public:
		LogFunction();
		~LogFunction();

		virtual shared_ptr<Data> run() override;
	};

}
