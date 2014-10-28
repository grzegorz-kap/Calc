#include "stdafx.h"
#include "LuFunction.h"


namespace PR
{
	LuFunction::LuFunction()
	{
		min_args_count = max_args_count = 1;
	}


	LuFunction::~LuFunction()
	{
	}

	shared_ptr<Data> LuFunction::run()
	{
		auto out = make_shared<Output>();
		auto &vec = out->getOutput();
		vec.assign(output, shared_ptr<Data>());
		switch (output)
		{
		case 1: arguments[0]->lu(vec[0]); break;
		case 2: arguments[0]->lu(vec[0],vec[1]); break;
		case 3: arguments[0]->lu(vec[0], vec[1], vec[2]); break;
		}
		return out;
	}
}
