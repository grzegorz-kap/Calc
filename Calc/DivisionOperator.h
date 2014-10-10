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

		virtual shared_ptr<Data> evaluate() override;
	};

}
