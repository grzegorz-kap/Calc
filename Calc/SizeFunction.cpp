#include "stdafx.h"
#include "SizeFunction.h"


namespace PR
{
	SizeFunction::SizeFunction()
	{
		max_args_count = min_args_count = 1;
		name = "size";
	}


	SizeFunction::~SizeFunction()
	{
	}

	shared_ptr<Data> SizeFunction::run()
	{
		shared_ptr<Output> output = std::make_shared<Output>();
		
		output->add(arguments[0]->get_rows());
		output->add(arguments[0]->get_cols());

		return std::move(output);
	}
}
