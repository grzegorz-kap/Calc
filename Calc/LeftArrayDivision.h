#pragma once
#include "Operator.h"

namespace PR
{
	class LeftArrayDivision :
		public Operator
	{
	public:
		LeftArrayDivision();
		~LeftArrayDivision();

		virtual shared_ptr<Data> evaluate() override
		{
 			return arguments[1]->rdivide(arguments[0]);
		}
	};
}

