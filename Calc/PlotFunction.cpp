#include "stdafx.h"
#include "PlotFunction.h"


namespace PR
{
	PlotFunction::PlotFunction()
	{
		min_args_count = 2;
		max_args_count = 2;
		name = "plot";
	}


	PlotFunction::~PlotFunction()
	{
	}

	shared_ptr<Data> PlotFunction::run()
	{
		GraphDrawer graph;
		auto x = arguments[0]->toDoubleVector();
		auto y = arguments[1]->toDoubleVector();
		if (x.size() && y.size())
			graph.plot(&x[0], &y[0], x.size(), y.size());
		return make_shared<Output>();
	}

}