#include "stdafx.h"
#include "ModFunction.h"

namespace KLab
{
	ModFunction::ModFunction()
	{
		min_args_count = 2;
		max_args_count = 2;
		name = "mod";
	}

	ModFunction::~ModFunction()
	{
	}

	shared_ptr<Data> ModFunction::run()
	{
		if (!arguments[0]->isReal() || !arguments[1]->isReal())
			throw NumericException(string("Error using 'mod': arguments must be real."));
		return arguments[0]->cmod(arguments[1]);
	}
}