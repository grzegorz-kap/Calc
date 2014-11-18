#pragma once
#include "Operator.h"

namespace PR
{
	class LogicalNotOperator :
		public Operator
	{
	public:
		LogicalNotOperator();
		~LogicalNotOperator();

		virtual shared_ptr<Data> evaluate() override;
	};
}

