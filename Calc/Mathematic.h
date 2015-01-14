#pragma once

#include "NumericException.h"
#include "Matrix.h"
#include "MatrixBuilder.h"


#include <boost\math\constants\constants.hpp>

using namespace boost::math::constants;



namespace PR
{
	template <class X> class Matrix;
	template <class X> class ComplexNumber;

	class Mathematic
	{
	public:
		Mathematic() = delete;
		~Mathematic() = delete;

		template<class T> static Matrix<T> power(const Matrix<T> &a, const Matrix<T> &b);
		template<class T> static ComplexNumber<T> power(const ComplexNumber<T> &a, const ComplexNumber<T> &b);
		template<class T> static Matrix<T> power(const Matrix<T> &a, const ComplexNumber<T> &b);
		template<class T> static Matrix<T>  mpower(const Matrix<T> &a, const Matrix<T> &b);
		template<class T> static ComplexNumber<T> mpower(const ComplexNumber<T> &a, const ComplexNumber<T> &b);
		template<class T> static Matrix<T> logarithm(const Matrix<T> &a, const Matrix<T> &b);
		template<class T> static Matrix<T> logarithm(const Matrix<T> &a);
		template<class T> static ComplexNumber<T> logarithm(const ComplexNumber<T> &a, const ComplexNumber<T> &b);
		template<class T> static ComplexNumber<T> logarithm(const ComplexNumber<T> &b);
		template<class T> static Matrix<T> logarithm10(const Matrix<T> &b);
		template<class T> static ComplexNumber<T> logarithm10(const ComplexNumber<T> &b);
		template<class T> static Matrix<T> logarithm2(const Matrix<T> &b);
		template<class T> static ComplexNumber<T> logarithm2(const ComplexNumber<T> &b);
		template <class T> static T argument(const ComplexNumber<T> &z);
		template <class T> static T module(const ComplexNumber<T> &z);
		template <class T> static ComplexNumber<T> sinus(const ComplexNumber<T> &z);
		template <class T> static Matrix<T> sinus(const Matrix<T> &m);
		template <class T> static ComplexNumber<T> cosinus(const ComplexNumber<T> &a);
		template <class T> static Matrix<T> cosinus(const Matrix<T> &a);
		template <class T> static ComplexNumber<T> tangens(const ComplexNumber<T> &a);
		template <class T> static Matrix<T> tangens(const Matrix<T> &a);
		template <class T> static ComplexNumber<T> cotangens(const ComplexNumber<T> &a);
		template <class T> static Matrix<T> cotangens(const Matrix<T> &a);
		template <class T> static T fix(const T &value);
		template <class T> static ComplexNumber<T> fix(const ComplexNumber<T> &value);
		template <class T> static Matrix<T> fix(const Matrix<T> &value);
		template <class T> static ComplexNumber<T> cfloor(const ComplexNumber<T> &a);
		template <class T> static Matrix<T> cfloor(const Matrix<T> &A);
		template <class T> static ComplexNumber<T> cceil(const ComplexNumber<T> &a);
		template <class T> static Matrix<T> cceil(const Matrix<T> &A);
		template <class T> static ComplexNumber<T> cmod(const ComplexNumber<T> &a, const ComplexNumber<T> &b);
		template <class T> static Matrix<T> cmod(const Matrix<T> &A, const ComplexNumber<T> &b);
		template <class T> static Matrix<T> cmod(const Matrix<T> &A, const Matrix<T> &B);
		template <class T> static ComplexNumber<T> cround(const ComplexNumber<T> &a);
		template <class T> static Matrix<T> cround(const Matrix<T> &A);

	};
}

