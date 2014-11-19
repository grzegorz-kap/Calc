#include "stdafx.h"
#include "AndOperator.h"


namespace PR
{
	AndOperator::AndOperator()
		:Operator("&&",100,2,EVAULATED::RIGHT)
	{
		set_class(TOKEN_CLASS::SHORT_CIRCUIT_OP);
	}


	AndOperator::~AndOperator()
	{
	}

	shared_ptr<Data> AndOperator::evaluate()
	{
		throwIfNot("Data must be convertible to logical scalar values.",[](const shared_ptr<Data> &data){
			return data->isScalar(); 
		});

		return make_shared<ComplexNumber<double>>(*arguments[0] == true && *arguments[1] == true);
	}

}