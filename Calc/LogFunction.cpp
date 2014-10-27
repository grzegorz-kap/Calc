#include "stdafx.h"
#include "LogFunction.h"


namespace PR
{
	LogFunction::LogFunction()
	{
		min_args_count = 1;
		max_args_count = 2;
	}


	LogFunction::~LogFunction()
	{
	}

	shared_ptr<Data> LogFunction::run()
	{
		if (arguments.size() == 1)
			return arguments[0]->log();
		else
			return arguments[0]->log(arguments[1]);
	}
}
