#include "stdafx.h"
#include "LogicalNotOperator.h"


namespace PR
{
	LogicalNotOperator::LogicalNotOperator()
		:Operator("~",20,1,EVAULATED::LEFT)
	{
	}


	LogicalNotOperator::~LogicalNotOperator()
	{
	}


	shared_ptr<Data> LogicalNotOperator::evaluate()
	{
		if (!arguments[0]->isReal())
			throw NumericException(string("'~' operand must be real."));

		return !*arguments[0];
	}
}