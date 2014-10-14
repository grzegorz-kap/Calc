#pragma once
#include "Operator.h"
namespace PR
{
	class MatrixExponentiationOperator :
		public Operator
	{
	public:
		MatrixExponentiationOperator();
		~MatrixExponentiationOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->mexponentiation(arguments[1]);
		}
	};

}
