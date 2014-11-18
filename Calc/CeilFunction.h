#pragma once
#include "Function.h"

namespace PR
{
	class CeilFunction :
		public Function
	{
	public:
		CeilFunction();
		~CeilFunction();

		virtual shared_ptr<Data> run() override;
	};


}