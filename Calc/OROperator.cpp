#include "stdafx.h"
#include "OROperator.h"


namespace PR
{
	OROperator::OROperator()
		:Operator("||",110,2,EVAULATED::RIGHT)
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
}
