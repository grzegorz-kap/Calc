#include "stdafx.h"
#include "Function.h"


namespace PR
{
	Function::Function()
	{
	}


	Function::~Function()
	{
	}

	shared_ptr<Data> Function::run()
	{
		throw CalcException("Unimplemented function behaviour!");
	}

	void Function::set(const vector<shared_ptr<Data>> &args)
	{
		checkArgsCount(args.size());
		arguments = args;
	}

	void Function::checkArgsCount(int i)
	{
		if (min_args_count == max_args_count == -1)
			return;

		if (i<min_args_count || i>max_args_count)
			throw CalcException("Wrong number of parameters in function call '"+name+"'.");
	}

}