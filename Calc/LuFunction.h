#pragma once
#include "Function.h"

namespace PR
{
	class LuFunction :
		public Function
	{
	public:
		LuFunction();
		~LuFunction();

		virtual shared_ptr<Data> run() override;
	};

}
