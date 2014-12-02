#include "stdafx.h"
#include "RelationalOperators.h"

namespace PR
{
	EqOperator::EqOperator()
		:Operator("==", 70, 2, EVAULATED::RIGHT)
	{
	}
	EqOperator::~EqOperator()
	{
	}
	shared_ptr<Data> EqOperator::evaluate()
	{
		return arguments[0]->eq(arguments[1]);
	}



	GeOperator::GeOperator()
		:Operator(">=", 70, 2, EVAULATED::RIGHT)
	{
	}
	GeOperator::~GeOperator()
	{
	}
	shared_ptr<Data> GeOperator::evaluate()
	{
		return arguments[0]->ge(arguments[1]);
	}


	GtOperator::GtOperator()
		:Operator(">", 70, 2, EVAULATED::RIGHT)
	{
	}
	GtOperator::~GtOperator()
	{
	}
	shared_ptr<Data> GtOperator::evaluate()
	{
		return arguments[0]->gt(arguments[1]);
	}



	LeOperator::LeOperator()
		:Operator("<=", 70, 2, EVAULATED::RIGHT)
	{
	}

	LeOperator::~LeOperator()
	{
	}
	shared_ptr<Data> LeOperator::evaluate()
	{
		return arguments[0]->le(arguments[1]);
	}



	LTOperator::LTOperator()
		:Operator("<", 70, 2, EVAULATED::RIGHT)
	{
	}
	LTOperator::~LTOperator()
	{
	}
	shared_ptr<Data> LTOperator::evaluate()
	{
		return arguments[0]->lt(arguments[1]);
	}


	NeOperator::NeOperator()
		:Operator("!=", 70, 2, EVAULATED::RIGHT)
	{
	}
	NeOperator::~NeOperator()
	{
	}
	shared_ptr<Data> NeOperator::evaluate()
	{
		return arguments[0]->ne(arguments[1]);
	}
}