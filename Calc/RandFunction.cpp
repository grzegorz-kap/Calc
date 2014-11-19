#include "stdafx.h"
#include "RandFunction.h"


namespace PR
{
	bool RandFunction::random_generator_initiated = false;

	RandFunction::RandFunction()
	{
		min_args_count = 1;
		max_args_count = 2;
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
}