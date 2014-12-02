#include "stdafx.h"
#include "PlotingFunctions.h"

namespace PR
{
	extern template class Matrix < double >;
	extern template class Matrix < hdouble >;
	extern template class ComplexNumber < double >;
	extern template class ComplexNumber < hdouble >;
	extern template class Numeric < Matrix<double> >;
	extern template class Numeric < Matrix<hdouble> >;
	extern template class Numeric < ComplexNumber<double> >;
	extern template class Numeric < ComplexNumber<hdouble> >;

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

		if (x.size() != y.size() || x.size() != y.size() || x.size() != z.size())
			throw CalcException("Error using plot. Vectors must be the same lengths.");

		if (x.size() == 0)
			return make_shared<Output>();

		graph.plot3(&x[0], &y[0], &z[0], x.size(), y.size(), z.size());

		return make_shared<Output>();
	}

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

		size sx = size(arguments[0]->get_rows_int(), arguments[0]->get_cols_int());
		size sy = size(arguments[1]->get_rows_int(), arguments[1]->get_cols_int());
		size sz = size(arguments[2]->get_rows_int(), arguments[2]->get_cols_int());

		if (sz.m != sy.n || sz.n != sx.m)
			throw CalcException("Calc");

		GraphDrawer graph;
		graph.surface(&x[0], &y[0], &z[0], sx, sy, sz);

		return make_shared<Output>();
	}
}