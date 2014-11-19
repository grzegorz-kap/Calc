#pragma once
#include "Function.h"

namespace PR
{
	class DetFunction :
		public Function
	{
	public:
		DetFunction();
		~DetFunction();
		virtual shared_ptr<Data> run() override;
	};
}

