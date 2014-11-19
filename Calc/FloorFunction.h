#pragma once
#include "Function.h"

namespace PR
{
	class FloorFunction :
		public Function
	{
	public:
		FloorFunction();
		~FloorFunction();

		virtual shared_ptr<Data> run() override;
	};
}

