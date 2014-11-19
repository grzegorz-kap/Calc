#include "stdafx.h"
#include "FloorFunction.h"


namespace PR
{
	FloorFunction::FloorFunction()
	{
		min_args_count = 1;
		max_args_count = 2;
		name = "floor";
	}


	FloorFunction::~FloorFunction()
	{
	}

	shared_ptr<Data> FloorFunction::run()
	{
		return arguments[0]->cfloor();
	}
}
