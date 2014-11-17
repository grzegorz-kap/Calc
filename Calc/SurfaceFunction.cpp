#include "stdafx.h"
#include "SurfaceFunction.h"


namespace PR
{

	SurfaceFunction::SurfaceFunction()
	{
		min_args_count = 3;
		max_args_count = 3;
		name = "surface";
	}


	SurfaceFunction::~SurfaceFunction()
	{
	}

	shared_ptr<Data> SurfaceFunction::run()
	{
		auto x = arguments[0]->toDoubleVector();
		auto y = arguments[1]->toDoubleVector();
		auto z = arguments[2]->toDoubleVectorAll();

		GraphDrawer graph;
		graph.surface(&x[0], &y[0], &z[0], size(1, x.size()), size(1, y.size()), size(arguments[2]->get_rows_int(), arguments[2]->get_cols_int()));

		return make_shared<Output>();
	}
}
