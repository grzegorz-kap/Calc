#pragma once
#include "Operator.h"

namespace PR
{
	class GeOperator :
		public Operator
	{
	public:
		GeOperator();
		~GeOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->ge(arguments[1]);
		}
	};
}

