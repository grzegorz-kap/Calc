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

		size sx = size(arguments[0]->get_rows_int(),arguments[0]->get_cols_int());
		size sy = size(arguments[1]->get_rows_int(), arguments[1]->get_cols_int());
		size sz = size(arguments[2]->get_rows_int(), arguments[2]->get_cols_int());

		if (sz.m != sy.n || sz.n != sx.m)
			throw CalcException("Calc");

		GraphDrawer graph;
		graph.surface(&x[0], &y[0], &z[0],sx, sy,sz);

		return make_shared<Output>();
	}
}
