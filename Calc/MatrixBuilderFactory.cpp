#include "stdafx.h"
#include "MatrixBuilderFactory.h"


namespace PR
{
	unique_ptr<IMatrixBuilder> MatrixBuilderFactory::get(TYPE _type)
	{
		switch (_type)
		{
		case TYPE::M_DOUBLE:
			return make_unique<MatrixBuilder<double>>();
		case TYPE::M_INT:
			return make_unique < MatrixBuilder<int>>();
		}
	}
}
