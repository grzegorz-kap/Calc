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
		arguments = args;
	}

	void Function::checkArgsCount(int i)
	{
		if (i<min_args_count || i>max_args_count)
			throw CalcException("Wrong number of parameters");
	}

}