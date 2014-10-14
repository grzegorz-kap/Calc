#pragma once
#include "Operator.h"
namespace PR
{
	class NeOperator :
		public Operator
	{
	public:
		NeOperator();
		~NeOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->ne(arguments[1]);
		}
	};
}

