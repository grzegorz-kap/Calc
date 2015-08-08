#include "stdafx.h"
#include "TrigonometryFunctions.h"

namespace KLab
{
	CosFun::CosFun()
	{
		min_args_count = max_args_count = 1;
		name = "sin";
	}

	CosFun::~CosFun()
	{
	}

	shared_ptr<Data> CosFun::run()
	{
		return arguments[0]->cos();
	}

	SinFun::SinFun()
	{
		min_args_count = max_args_count = 1;
		name = "sin";
	}

	SinFun::~SinFun()
	{
	}

	shared_ptr<Data> SinFun::run()
	{
		return arguments[0]->sin();
	}

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

	CotanFun::CotanFun()
	{
		max_args_count = min_args_count = 1;
		name = "cot";
	}

	CotanFun::~CotanFun()
	{
	}

	shared_ptr<Data> CotanFun::run()
	{
		return arguments[0]->cot();
	}
}