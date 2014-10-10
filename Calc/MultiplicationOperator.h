#pragma once
#include "Operator.h"

namespace PR
{
	class MultiplicationOperator :
		public Operator
	{
	public:
		MultiplicationOperator();
		~MultiplicationOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return *arguments[0] * arguments[1];
		}
	};
}