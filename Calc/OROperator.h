#pragma once
#include "Operator.h"

namespace PR
{
	class OROperator :
		public Operator
	{
	public:
		OROperator();
		~OROperator();

		virtual shared_ptr<Data> evaluate() override;
	};

}
