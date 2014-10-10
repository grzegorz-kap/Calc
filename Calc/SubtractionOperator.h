#pragma once
#include "Operator.h"

namespace PR
{
	class SubtractionOperator :
		public Operator
	{
	public:
		SubtractionOperator();
		~SubtractionOperator();

		virtual shared_ptr<Data> evaluate() override;
	};

}
