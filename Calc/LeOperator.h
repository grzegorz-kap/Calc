#pragma once
#include "Operator.h"

namespace PR
{
	class LeOperator
		:public Operator
	{
	public:
		LeOperator();
		~LeOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->le(arguments[1]);
		}
	};
}

