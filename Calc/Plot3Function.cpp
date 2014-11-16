#include "stdafx.h"
#include "Plot3Function.h"


namespace PR
{
	Plot3Function::Plot3Function()
	{
		min_args_count = 3;
		max_args_count = 3;
		name = "plot3";
	}


	Plot3Function::~Plot3Function()
	{
	}

	shared_ptr<Data> Plot3Function::run()
	{
		GraphDrawer graph;
		auto x = arguments[0]->toDoubleVector();
		auto y = arguments[1]->toDoubleVector();
		auto z = arguments[2]->toDoubleVector();

		if (x.size()!=y.size()||x.size()!=y.size()||x.size()!=z.size())
			throw CalcException("Error using plot. Vectors must be the same lengths.");

		if (x.size() == 0)
			return make_shared<Output>();

		graph.plot3(&x[0], &y[0], &z[0], x.size(), y.size(), z.size());

		return make_shared<Output>();
	}
}
