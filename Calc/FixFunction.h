#pragma once
#include "Function.h"

namespace PR
{
	class FixFunction :
		public Function
	{
	public:
		FixFunction();
		~FixFunction();

		virtual shared_ptr<Data> run() override;
	};
}

