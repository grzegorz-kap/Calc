#include "stdafx.h"
#include "FixFunction.h"


namespace PR
{
	FixFunction::FixFunction()
	{
		min_args_count = 1;
		max_args_count = 1;
		name = "fix";
	}


	FixFunction::~FixFunction()
	{
	}

	shared_ptr<Data> FixFunction::run()
	{
		return arguments[0]->cfix();
	}
}
