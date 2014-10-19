#pragma once
#include "Operator.h"
namespace PR
{
	class TranspositionOperator :
		public Operator
	{
	public:
		TranspositionOperator();
		~TranspositionOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->transposition();
		}
	};
}

