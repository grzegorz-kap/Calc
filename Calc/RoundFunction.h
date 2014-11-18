#pragma once
#include "Function.h"

namespace PR
{
	class RoundFunction :
		public Function
	{
	public:
		RoundFunction();
		~RoundFunction();

		virtual shared_ptr<Data> run() override;
	};
}

