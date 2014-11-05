#pragma once

#include <memory>
#include <vector>
#include <algorithm>

using std::vector;

#include "Data.h"
#include "Matrix.h"
#include "ComplexNumber.h"
#include "Output.h"
#include "MatrixBuilder.h"
#include "MatrixBuilderFactory.h"

namespace PR
{
	class TypePromotor
	{
		static bool(*ptr_max_lambda)(const shared_ptr<Data>&, const shared_ptr<Data>&);
	public:
		TypePromotor();
		~TypePromotor();

		static void promote(shared_ptr<Data> &a, shared_ptr<Data> &b);
		static void promote(vector<shared_ptr<Data>> &vec);
		static void promote(vector<shared_ptr<Data>> &vec, const TYPE &type);
		static void promote(shared_ptr<Data> &a, const TYPE &type);
		static void convertTo(TYPE type,const shared_ptr<Data> &a, shared_ptr<Data> &dest);
	private:
		
		static void convertOutputTo(TYPE type,const shared_ptr<Data> &a, shared_ptr<Data> &dest);
	};
}
