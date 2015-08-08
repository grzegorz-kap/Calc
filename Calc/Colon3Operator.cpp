#include "stdafx.h"
#include "Colon3Operator.h"

namespace PR
{
	Colon3Operator::Colon3Operator()
		:Operator("$:", 60, 3, EVAULATED::RIGHT)
	{
	}

	Colon3Operator::~Colon3Operator()
	{
	}
}