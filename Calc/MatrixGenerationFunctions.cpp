#include "stdafx.h"
#include "MatrixGenerationFunctions.h"


namespace PR
{
	extern template class Matrix < double > ;
	extern template class Matrix < hdouble > ;
	extern template class ComplexNumber < double > ;
	extern template class ComplexNumber < hdouble > ;
	extern template class MatrixBuilder < double > ;
	extern template class MatrixBuilder < hdouble > ;

	bool RandFunction::random_generator_initiated = false;
	RandFunction::RandFunction()
	{
		min_args_count = 1;
		max_args_count = 2;
		name = "rand";
	}
	RandFunction::~RandFunction()
	{
	}
	shared_ptr<Data> RandFunction::run()
	{
		init_rand_generator();
		
		if (!arguments[0]->isInteger() || arguments.size() > 1 && !arguments[1]->isInteger())
			throw CalcException("Error using 'rand'. Size input is not integer.");

		int m = arguments[0]->toInteger();
		int n = arguments.size() > 1 ? arguments[1]->toInteger() : m;

		return make_shared<Matrix<double>>(MatrixBuilder<double>::buildRand(m, n));
	}
	void RandFunction::init_rand_generator()
	{
		if (!random_generator_initiated)
		{
			std::srand(time(0));
			random_generator_initiated = true;
		}
	}


	OnesFunction::OnesFunction()
	{
		min_args_count = 1;
		max_args_count = 2;
		name = "ones";
	}

	OnesFunction::~OnesFunction()
	{

	}

	shared_ptr<Data> OnesFunction::run()
	{
		if (!arguments[0]->isInteger() || arguments.size() > 1 && !arguments[1]->isInteger())
			throw CalcException("Error using 'ones'. Size input is not integer.");
		int m = arguments[0]->toInteger();
		int n = arguments.size() > 1 ? arguments[1]->toInteger() : m;
		return make_shared<Matrix<double>>(m, n, ComplexNumber<double>(1));
	}


	EyeFunction::EyeFunction()
	{
		min_args_count = 1;
		max_args_count = 2;
		name = "eye";
	}
	EyeFunction::~EyeFunction()
	{

	}
	shared_ptr<Data> EyeFunction::run()
	{
		if (!arguments[0]->isInteger() || arguments.size() > 1 && !arguments[1]->isInteger())
			throw CalcException("Error using 'eye'. Size input is not integer.");
		int m = arguments[0]->toInteger();
		int n = arguments.size() > 1 ? arguments[1]->toInteger() : m;
		return make_shared<Matrix<double>>(MatrixBuilder<double>::buildEye(m, n));
	}


	ZerosFunction::ZerosFunction()
	{
		min_args_count = 1;
		max_args_count = 2;
		name = "zeros";
	}
	ZerosFunction::~ZerosFunction()
	{

	}
	shared_ptr<Data> ZerosFunction::run()
	{
		if (!arguments[0]->isInteger() || arguments.size() > 1 && !arguments[1]->isInteger())
			throw CalcException("Error using 'zeros'. Size input is not integer.");
		int m = arguments[0]->toInteger();
		int n = arguments.size() > 1 ? arguments[1]->toInteger() : m;
		return make_shared<Matrix<double>>(m,n,ComplexNumber<double>(0));
	}
}