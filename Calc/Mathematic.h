#pragma once

#include <cmath>

#include "NumericException.h"
#include "Matrix.h"
#include "ComplexNumber.h"
#include <boost\math\constants\constants.hpp>

using namespace boost::math::constants;
using std::pow;

template <class X>
class Matrix;

template <class X>
class ComplexNumber;

namespace PR
{
	class Mathematic
	{
	public:
		Mathematic() = delete;
		~Mathematic() = delete;

		template<class T, class U>
		static auto power(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (b.isScalar())
				return Mathematic::power(a, b.mx[0][0]);

			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < C.M; i++)
				for (int j = 0; j < C.N; j++)
					C.mx[i][j] = Mathematic::power(a.mx[i][j], b.mx[i][j]);
			return C;
		}

		template<class T, class U>
		static auto power(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			if (a.im == 0 && b.im == 0)
				return ComplexNumber<decltype(T() + U())>(pow(a.re, b.re));

			ComplexNumber<T> E(e<T>());
			auto y = b*logarithm(E, a);
			ComplexNumber<T> out;
			out.re = out.im = pow(E.re, y.re);
			out.re = out.re*cos(y.im);
			out.im = out.im*sin(y.im);
			return out;
		}

		template <class T, class U>
		static auto power(const Matrix<T> &a, const ComplexNumber<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					C.mx[i][j] = Mathematic::power(a.mx[i][j], b);
			return C;
		}

		/*template <class T, class U>
		static auto power(const ComplexNumber<T> &a, const Matrix<U> &b)
			->ComplexNumber < decltype(T() + U()) >
		{
			if (!b.isScalar())
				throw "!";

			return power(a, b.mx[0][0]);
		}*/

		/* Matrix exponentiation */
		template<class T, class U>
		static auto mpower(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (a.isScalar() && b.isScalar())
				return Mathematic::power(a.mx[0][0], b.mx[0][0]);

			throw CalcException("Matrix ^ Matrix to be implemented in the feature!");
		}

		/*template <class T, class U>
		static auto mpower(const ComplexNumber<T> &a, const Matrix<U> &b)
			->ComplexNumber < decltype(T() + U()) >
		{
			if (!b.isScalar())
				throw "!";

			return Mathematic::power(a, b.mx[0][0]);
		}*/

		template<class T, class U>
		static auto mpower(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			return power(a, b);
		}


		template <class T, class U>
		static auto logarithm(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			if (a.re == 0 && a.im == 0)
				NumericException::throwLogarithmZeroBase();
			if (b.re == 0 && b.im == 0)
				NumericException::throwLogarithmFromZero();

			if (a.im == 0 && b.im == 0)
				return ComplexNumber<decltype(T() + U())>(log(b.re) / log(a.re));

			return ComplexNumber<decltype(T() + U())>(log(module(b)), argument(b)) / ComplexNumber<decltype(T() + U())>(log(module(a)), argument(a));
		}

		/* Argument of complex number */
		template <class T>
		static T argument(const ComplexNumber<T> &z)
		{
			if (z.re > 0)
				return atan(z.im / z.re);
			if (z.re < 0)
				return atan(z.im / z.re) + pi<T>();
			if (z.im>0)
				return 0.5*pi<T>();
			if (z.im < 0)
				return -0.5*pi<T>();
			return 0;
		}

		/* Module of complex number */
		template <class T>
		static T module(const ComplexNumber<T> &z)
		{
			return sqrt(z.re*z.re + z.im*z.im);
		}
	};
}

