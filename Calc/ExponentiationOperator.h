#pragma once
#include "Operator.h"

namespace PR
{
	class ExponentiationOperator :
		public Operator
	{
	public:
		ExponentiationOperator();
		~ExponentiationOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->exponentiation(arguments[1]);
		}
	};
}

