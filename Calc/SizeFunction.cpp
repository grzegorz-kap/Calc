#include "stdafx.h"
#include "SizeFunction.h"


namespace PR
{
	SizeFunction::SizeFunction()
	{
		max_args_count = min_args_count = 1;
	}


	SizeFunction::~SizeFunction()
	{
	}

	shared_ptr<Data> SizeFunction::run()
	{
		shared_ptr<IMatrix<mytype>> result(new IMatrix<mytype>(1, 2,0.0,0.0));
		
		(*result)(0, 0) = arg1->rows();
		(*result)(0, 1) = arg1->cols();

		return result;
	}

	void SizeFunction::set(const vector<shared_ptr<Data>> &args)
	{
		checkArgsCount(args.size());
		arg1 = IMatrix<mytype>::cast_i(args[0]);
	}
}
