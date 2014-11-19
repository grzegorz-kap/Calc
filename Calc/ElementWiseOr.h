#pragma once
#include "Operator.h"

namespace PR
{
	class ElementWiseOr :
		public Operator
	{
	public:
		ElementWiseOr();
		~ElementWiseOr();

		virtual shared_ptr<Data> evaluate() override;
	};

}
