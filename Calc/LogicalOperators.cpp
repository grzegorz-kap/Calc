#include "stdafx.h"
#include "LogicalOperators.h"

namespace KLab
{
	AndOperator::AndOperator()
		:Operator("&&", 100, 2, EVAULATED::RIGHT)
	{
	}
	AndOperator::~AndOperator()
	{
	}
	shared_ptr<Data> AndOperator::evaluate()
	{
		throwIfNot("Data must be convertible to logical scalar values.", [](const shared_ptr<Data> &data){
			return data->isScalar();
		});
		return make_shared<ComplexNumber<double>>(*arguments[0] == true && *arguments[1] == true);
	}

	OROperator::OROperator()
		:Operator("||", 110, 2, EVAULATED::RIGHT)
	{
	}
	OROperator::~OROperator()
	{
	}
	shared_ptr<Data> OROperator::evaluate()
	{
		throwIfNot("Data must be convertible to logical scalar values.", [](const shared_ptr<Data> &data){
			return data->isScalar();
		});
		return make_shared<ComplexNumber<double>>(*arguments[0] == true || *arguments[1] == true);
	}

	ElementWiseAnd::ElementWiseAnd()
		:Operator("&", 80, 2, EVAULATED::RIGHT)
	{
	}
	ElementWiseAnd::~ElementWiseAnd()
	{
	}
	shared_ptr<Data> ElementWiseAnd::evaluate()
	{
		if (!arguments[0]->isReal() || !arguments[1]->isReal())
			throw NumericException(string("'&' operands must be real."));

		return *arguments[0] & arguments[1];
	}

	ElementWiseOr::ElementWiseOr()
		:Operator("|", 90, 2, EVAULATED::RIGHT)
	{
	}

	ElementWiseOr::~ElementWiseOr()
	{
	}
	shared_ptr<Data> ElementWiseOr::evaluate()
	{
		if (!arguments[0]->isReal() || !arguments[1]->isReal())
			throw NumericException(string("'|' operands must be real."));

		return *arguments[0] | arguments[1];
	}

	LogicalNotOperator::LogicalNotOperator()
		:Operator("~", 20, 1, EVAULATED::LEFT)
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