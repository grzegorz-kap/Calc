#include "stdafx.h"
#include "CeilFunction.h"


namespace PR
{
	CeilFunction::CeilFunction()
	{
		min_args_count = 1;
		max_args_count = 1;
		name = "ceil";
	}


	CeilFunction::~CeilFunction()
	{
	}

	shared_ptr<Data> CeilFunction::run()
	{
		return arguments[0]->cceil();
	}
}
