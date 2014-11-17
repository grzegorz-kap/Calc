#pragma once
#include "Function.h"
#include "GraphDrawer.h"

namespace PR
{
	class Plot3Function :
		public Function
	{
	public:
		Plot3Function();
		~Plot3Function();

		shared_ptr<Data> run() override;
	};
}

