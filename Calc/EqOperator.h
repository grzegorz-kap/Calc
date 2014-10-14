#pragma once
#include "Operator.h"

namespace PR
{
	class EqOperator :
		public Operator
	{
	public:
		EqOperator();
		~EqOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->eq(arguments[1]);
		}
	};
}

