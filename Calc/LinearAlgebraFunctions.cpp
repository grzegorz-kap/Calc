#include "stdafx.h"
#include "LinearAlgebraFunctions.h"

namespace KLab
{
	DetFunction::DetFunction()
	{
		min_args_count = max_args_count = 1;
		name = "det";
	}

	DetFunction::~DetFunction()
	{
	}

	shared_ptr<Data> DetFunction::run()
	{
		return arguments[0]->det();
	}

	UrlFunction::UrlFunction()
	{
		min_args_count = max_args_count = 2;
		name = "url";
	}

	UrlFunction::~UrlFunction()
	{
	}

	shared_ptr<Data> UrlFunction::run()
	{
		return arguments[0]->url(arguments[1]);
	}

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
		if (arguments[0]->get_rows_int() != arguments[0]->get_cols_int())
			throw NumericException(string("inv(A). A must be square matrix."));
		return arguments[0]->inv();
	}

	LuFunction::LuFunction()
	{
		min_args_count = max_args_count = 1;
		name = "lu";
	}

	LuFunction::~LuFunction()
	{
	}

	shared_ptr<Data> LuFunction::run()
	{
		auto out = make_shared<Output>();
		auto &vec = out->getOutput();
		vec.assign(output, shared_ptr<Data>()); /*output is number of expected outputs */
		switch (output)
		{
		case 1: arguments[0]->lu(vec[0]); break;
		case 2: arguments[0]->lu(vec[0], vec[1]); break;
		case 3: arguments[0]->lu(vec[0], vec[1], vec[2]); break;
		}
		return out;
	}

	ConjFunction::ConjFunction()
	{
		min_args_count = max_args_count = 1;
		name = "conj";
	}

	ConjFunction::~ConjFunction()
	{
	}

	shared_ptr<Data> ConjFunction::run()
	{
		return arguments[0]->conj();
	}
}