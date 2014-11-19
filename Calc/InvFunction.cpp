#include "stdafx.h"
#include "InvFunction.h"


namespace PR
{
	InvFunction::InvFunction()
	{
		min_args_count = max_args_count = 1;
		name = "inv";
	}


	InvFunction::~InvFunction()
	{
	}

	shared_ptr<Data> InvFunction::run()
	{
		return arguments[0]->inv();
	}

}