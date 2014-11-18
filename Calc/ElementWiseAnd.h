#pragma once
#include "Operator.h"

namespace PR
{
	class ElementWiseAnd :
		public Operator
	{
	public:
		ElementWiseAnd();
		~ElementWiseAnd();

		virtual shared_ptr<Data> evaluate() override;
	};
}

