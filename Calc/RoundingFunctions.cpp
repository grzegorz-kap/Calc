#include "stdafx.h"
#include "RoundingFunctions.h"

namespace PR
{
	CeilFunction::CeilFunction()
	{
		min_args_count = 1;
		max_args_count = 1;
		name = "ceil";
	}

	CeilFunction::~CeilFunction()
	{
	}

	shared_ptr<Data> CeilFunction::run()
	{
		return arguments[0]->cceil();
	}

	FixFunction::FixFunction()
	{
		min_args_count = 1;
		max_args_count = 1;
		name = "fix";
	}


	FixFunction::~FixFunction()
	{
	}

	shared_ptr<Data> FixFunction::run()
	{
		return arguments[0]->cfix();
	}

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

	RoundFunction::RoundFunction()
	{
		min_args_count = 1;
		max_args_count = 1;
		name = "round";
	}


	RoundFunction::~RoundFunction()
	{
	}

	shared_ptr<Data> RoundFunction::run()
	{
		return arguments[0]->cround();
	}
}