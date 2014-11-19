#include "stdafx.h"
#include "Log2Function.h"


namespace PR
{
	Log2Function::Log2Function()
	{
		min_args_count = max_args_count = 1;
		name = "log2";
	}


	Log2Function::~Log2Function()
	{
	}

	shared_ptr<Data> Log2Function::run()
	{
		return arguments[0]->log2();
	}
}
