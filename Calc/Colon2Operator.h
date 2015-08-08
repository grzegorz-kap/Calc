#pragma once
#include "Operator.h"

namespace PR
{
	class Colon2Operator :
		public Operator
	{
	public:
		Colon2Operator();
		~Colon2Operator();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->createVector(arguments[1]);
		}

		virtual void promoteArguments() override
		{
			promoteToMatrix();
		}

		virtual bool isColon2Operator() const override{ return true; }
	};
}
