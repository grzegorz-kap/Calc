#pragma once
#include "Operator.h"

namespace PR
{
	class AndOperator :
		public Operator
	{
	public:
		AndOperator();
		~AndOperator();

		virtual shared_ptr<Data> evaluate() override;
	};
}

