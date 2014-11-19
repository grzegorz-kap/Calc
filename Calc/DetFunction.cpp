#include "stdafx.h"
#include "DetFunction.h"


namespace PR
{
	DetFunction::DetFunction()
	{
		min_args_count = max_args_count = 1;
		name = "det";
	}


	DetFunction::~DetFunction()
	{
	}

	shared_ptr<Data> DetFunction::run()
	{
		return arguments[0]->det();
	}
}
