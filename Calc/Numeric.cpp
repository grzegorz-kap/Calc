#include "stdafx.h"
#include "Numeric.h"

namespace PR
{
	template class Numeric < Matrix<double> > ;
	template class Numeric < Matrix<hdouble> > ;
	template class Numeric < ComplexNumber<double> > ;
	template class Numeric < ComplexNumber<hdouble> > ;
}