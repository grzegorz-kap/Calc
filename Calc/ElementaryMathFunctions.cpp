#include "stdafx.h"
#include "ElementaryMathFunctions.h"

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

	LogFunction::LogFunction()
	{
		min_args_count = 1;
		max_args_count = 2;
		name = "log";
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

	SqrtFunction::SqrtFunction()
	{
		min_args_count = 1;
		max_args_count = 1;
		name = "sqrt";
	}
	SqrtFunction::~SqrtFunction()
	{

	}

	shared_ptr<Data> SqrtFunction::run()
	{
		return arguments[0]->sqrt();
	}
}