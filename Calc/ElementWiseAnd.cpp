#include "stdafx.h"
#include "ElementWiseAnd.h"


namespace PR
{
	ElementWiseAnd::ElementWiseAnd()
		:Operator("&",80,2,EVAULATED::RIGHT)
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
}
