#include "stdafx.h"
#include "Log10Function.h"


namespace PR
{
	Log10Function::Log10Function()
	{
		min_args_count = max_args_count = 1;
		name = "log10";
	}


	Log10Function::~Log10Function()
	{
	}

	shared_ptr<Data> Log10Function::run()
	{
		return arguments[0]->log10();
	}
}
