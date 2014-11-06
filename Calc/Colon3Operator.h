#pragma once
#include "Operator.h"

namespace PR
{
	class Colon3Operator :
		public Operator
	{
	public:
		Colon3Operator();
		~Colon3Operator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->createVector(arguments[1],arguments[2]);
		}

		virtual void promoteArguments() override
		{
			promoteToMatrix();
		}
	};

}
