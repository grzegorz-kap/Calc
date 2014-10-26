#pragma once
#include "Operator.h"

namespace PR
{
	class UPlusOperator :
		public Operator
	{
	public:
		UPlusOperator();
		~UPlusOperator();

		virtual shared_ptr<Data> evaluate() override
		{
			return std::move(arguments[0]);
		}
	};
}

