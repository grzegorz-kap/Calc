#pragma once
#include "Operator.h"

namespace PR
{
	class RightArrayDivision :
		public Operator
	{
	public:
		RightArrayDivision();
		~RightArrayDivision();

		virtual shared_ptr<Data> evaluate() override
		{
			return arguments[0]->rdivide(arguments[1]);
		}
	};

}
