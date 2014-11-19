#include "stdafx.h"
#include "CosFun.h"


namespace PR
{
	CosFun::CosFun()
	{
		min_args_count = max_args_count = 1;
		name = "sin";
	}


	CosFun::~CosFun()
	{
	}

	shared_ptr<Data> CosFun::run()
	{
		return arguments[0]->cos();
	}

}