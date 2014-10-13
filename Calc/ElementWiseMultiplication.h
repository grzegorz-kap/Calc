#pragma once
#include "Operator.h"

namespace PR
{
	class ElementWiseMultiplication :
		public Operator
	{
	public:
		ElementWiseMultiplication();
		~ElementWiseMultiplication();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->times(arguments[1]);
		}
	};
}