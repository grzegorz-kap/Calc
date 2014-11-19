#include "stdafx.h"
#include "MatrixUtils.h"

namespace PR
{
	/* Set pointers to function for matrix division */
	decltype(Matrix<double>::matrix_divide) Matrix<double>::matrix_divide = MatrixUtils::divide < double > ;
	decltype(Matrix<hdouble>::matrix_divide) Matrix<hdouble>::matrix_divide = MatrixUtils::divide < hdouble > ;
}
	

	
	

	

	

	


	

	