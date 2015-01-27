#include "stdafx.h"
#include "MessagesFunction.h"

namespace PR
{
	ErrorFunction::ErrorFunction()
	{
		min_args_count = max_args_count = 1;
		name = "error";
	}

	ErrorFunction::~ErrorFunction()
	{

	}

	shared_ptr<Data> ErrorFunction::run()
	{
		if (arguments[0]->_type != TYPE::STRING)
			throw CalcException("Argument of 'error' function must be string");
		throw CalcException(arguments[0]->toString());
	}
}