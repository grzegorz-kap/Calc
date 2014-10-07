#pragma once

#include "Function.h"
#include "IMatrix.h"
#include "MatrixBuilder.h"

namespace PR
{
	class SizeFunction : public Function
	{
		shared_ptr<IMatrix<mytype>> arg1;
	public:
		SizeFunction();
		~SizeFunction();

		virtual shared_ptr<Data> run();
		virtual void set(const vector<shared_ptr<Data>> &args);
	};
}

