#pragma once
#include "Operator.h"

namespace PR
{
	class DivisionOperator :
		public Operator
	{
	public:
		DivisionOperator();
		~DivisionOperator();

		virtual unique_ptr<Data> evaluate() override
		{
			return *arguments[0]/arguments[0];
		}
	};

}
