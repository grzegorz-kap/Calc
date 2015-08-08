#include "stdafx.h"
#include "MatrixBuilderFactory.h"

namespace PR
{
	extern template class MatrixBuilder < double > ;
	extern template class MatrixBuilder < hdouble > ;

	unique_ptr<IMatrixBuilder> MatrixBuilderFactory::get(TYPE _type)
	{
		switch (_type)
		{
		case TYPE::DOUBLE:
		case TYPE::M_DOUBLE:
			return make_unique<MatrixBuilder<double>>();
		case TYPE::R_DOUBLE:
		case TYPE::RM_DOUBLE:
			return make_unique<MatrixBuilder<hdouble>>();
		}
		return nullptr;
	}
}