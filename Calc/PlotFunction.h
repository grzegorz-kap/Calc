#pragma once
#include "Function.h"

#include "GraphDrawer.h"

namespace PR
{
	class PlotFunction :
		public Function
	{
	public:
		PlotFunction();
		~PlotFunction();

		virtual shared_ptr<Data> run() override;
	};

}
