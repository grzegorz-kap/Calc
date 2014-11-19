#include "stdafx.h"
#include "ElementWiseOr.h"


namespace PR
{
	ElementWiseOr::ElementWiseOr()
		:Operator("|",90,2,EVAULATED::RIGHT)
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
}
