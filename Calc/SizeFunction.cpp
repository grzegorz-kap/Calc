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

	LengthFunction::LengthFunction()
	{
		max_args_count = min_args_count = 1;
		name = "length";
	}
	LengthFunction::~LengthFunction()
	{
	}
	shared_ptr<Data> LengthFunction::run()
	{
		int a = arguments[0]->get_rows_int();
		int b = arguments[0]->get_cols_int();
		return make_shared<ComplexNumber<double>>(max(a, b));
	}

	NumelFunction::NumelFunction()
	{
		max_args_count = min_args_count = 1;
		name = "numel";
	}
	NumelFunction::~NumelFunction()
	{
	}
	shared_ptr<Data> NumelFunction::run()
	{
		return make_shared<ComplexNumber<double>>(arguments[0]->get_rows_int()*arguments[0]->get_cols_int());
	}


	IsColumnFunction::IsColumnFunction()
	{
		max_args_count = min_args_count = 1;
		name = "iscolumn";
	}
	IsColumnFunction::~IsColumnFunction()
	{
	}
	shared_ptr<Data> IsColumnFunction::run()
	{
		return make_shared<ComplexNumber<double>>(arguments[0]->get_cols_int() == 1);
	}


	IsEmptyFunction::IsEmptyFunction()
	{
		max_args_count = min_args_count = 1;
		name = "isempty";
	}
	IsEmptyFunction::~IsEmptyFunction()
	{
	}
	shared_ptr<Data> IsEmptyFunction::run()
	{
		return make_shared<ComplexNumber<double>>(arguments[0]->get_cols_int() == 0 || arguments[0]->get_rows_int() == 0);
	}


	IsRowFunction::IsRowFunction()
	{
		max_args_count = min_args_count = 1;
		name = "isrow";
	}
	IsRowFunction::~IsRowFunction()
	{
	}
	shared_ptr<Data> IsRowFunction::run()
	{
		return make_shared<ComplexNumber<double>>( arguments[0]->get_rows_int() == 1);
	}


	IsScalarFunction::IsScalarFunction()
	{
		max_args_count = min_args_count = 1;
		name = "isscalar";
	}
	IsScalarFunction::~IsScalarFunction()
	{
	}
	shared_ptr<Data> IsScalarFunction::run()
	{
		return make_shared<ComplexNumber<double>>(arguments[0]->isScalar());
	}


	IsVectorFunction::IsVectorFunction()
	{
		max_args_count = min_args_count = 1;
		name = "isvector";
	}
	IsVectorFunction::~IsVectorFunction()
	{
	}
	shared_ptr<Data> IsVectorFunction::run()
	{
		return make_shared<ComplexNumber<double>>(arguments[0]->get_cols_int() == 1 || arguments[0]->get_rows_int() == 1);
	}
}
