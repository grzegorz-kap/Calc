#pragma once
#include "Operator.h"
#include "OperatorException.h"

namespace PR
{
	class AdditionOperator :
		public Operator 
	{
	public:
		AdditionOperator();
		~AdditionOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return *arguments[0] + arguments[1];
		}
	};
}

