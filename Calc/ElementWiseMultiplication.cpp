#include "stdafx.h"
#include "ElementWiseMultiplication.h"


namespace PR
{
	ElementWiseMultiplication::ElementWiseMultiplication()
		:Operator(".*",40,2,EVAULATED::RIGHT)
	{
	}


	ElementWiseMultiplication::~ElementWiseMultiplication()
	{
	}
}
