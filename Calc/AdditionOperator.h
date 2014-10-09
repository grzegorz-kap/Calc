#pragma once
#include "Operator.h"
#include "OperatorException.h"

namespace PR
{
	class AdditionOperator :
		public Operator 
	{
	public:
		AdditionOperator();
		~AdditionOperator();
	};
}

