#pragma once
#include "Operator.h"

namespace PR
{
	class LTOperator :
		public Operator
	{
	public:
		LTOperator();
		~LTOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->lt(arguments[1]);
		}
	};
}

