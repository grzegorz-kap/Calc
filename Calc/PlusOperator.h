#pragma once
#include "Operator.h"
#include "OperatorException.h"

namespace PR
{
	class PlusOperator :
		public Operator 
	{
	public:
		PlusOperator();
		~PlusOperator();

		virtual shared_ptr<Data> evaluate(vector<shared_ptr<Data>> &stack);
	};
}

