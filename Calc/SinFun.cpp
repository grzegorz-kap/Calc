#include "stdafx.h"
#include "SinFun.h"


namespace PR
{
	SinFun::SinFun()
	{
		min_args_count = max_args_count = 1;
		name = "sin";
	}


	SinFun::~SinFun()
	{
	}

	shared_ptr<Data> SinFun::run()
	{
		return arguments[0]->sin();
	}
}
