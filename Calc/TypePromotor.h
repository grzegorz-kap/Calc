#pragma once

#include <memory>
#include <vector>
#include <algorithm>

using std::shared_ptr;
using std::vector;

#include "Data.h"
#include "Value.h"
#include "Matrix.h"
#include "ComplexNumber.h"

namespace PR
{
	class TypePromotor
	{
	public:
		TypePromotor();
		~TypePromotor();

		static void promote(shared_ptr<Data> &a, shared_ptr<Data> &b);
		static void promote(vector<shared_ptr<Data>> &vec);
		
	private:
		static void convertTo(TYPE type, shared_ptr<Data> &a, shared_ptr<Data> &dest);
	};
}
