#pragma once
#include "Operator.h"

namespace PR
{
	class USubtractionOperator :
		public Operator
	{
	public:
		USubtractionOperator();
		~USubtractionOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return -*arguments[0];
		}
	};

}
