#include "stdafx.h"
#include "TanFun.h"


namespace PR
{
	TanFun::TanFun()
	{
		max_args_count = min_args_count = 1;
		name = "tan";
	}


	TanFun::~TanFun()
	{
	}

	shared_ptr<Data> TanFun::run()
	{
		return arguments[0]->tan();
	}
}
