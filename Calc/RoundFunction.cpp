#include "stdafx.h"
#include "RoundFunction.h"


namespace PR
{
	RoundFunction::RoundFunction()
	{
		min_args_count = 1;
		max_args_count = 1;
		name = "round";
	}


	RoundFunction::~RoundFunction()
	{
	}

	shared_ptr<Data> RoundFunction::run()
	{
		return arguments[0]->cround();
	}
}