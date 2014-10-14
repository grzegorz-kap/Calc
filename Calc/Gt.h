#pragma once
#include "Operator.h"
namespace PR
{
	class Gt :
		public Operator
	{
	public:
		Gt();
		~Gt();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->gt(arguments[1]);
		}
	};
}

