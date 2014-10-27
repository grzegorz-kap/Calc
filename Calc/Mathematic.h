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

		template<class T, class U>
		static auto mpower(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (a.isScalar() && b.isScalar())
				return Mathematic::power(a.mx[0][0], b.mx[0][0]);

			throw CalcException("Matrix ^ Matrix to be implemented in the feature!");
		}

		template<class T, class U>
		static auto mpower(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			return power(a, b);
		}

		template<class T,class U>
		static auto logarithm(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (!a.isScalar())
				NumericException::throwMatrixLogDimensions();

			const ComplexNumber<T> &ref = a.mx[0][0];

			Matrix<decltype(T() + U())> C(b.M, b.N);
			for (int i = 0; i < b.M; i++)
				for (int j = 0; j < b.N; j++)
					C.mx[i][j] = logarithm(ref, b.mx[i][j]);
			return C;
		}

		template<class T>
		static Matrix<T> logarithm(const Matrix<T> &a)
		{
			Matrix<T> C(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					C.mx[i][j] = logarithm(a.mx[i][j]);
			return C;
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

		template <class T>
		static ComplexNumber<T> logarithm(const ComplexNumber<T> &b)
		{
			if (b.re == 0 && b.im == 0)
				NumericException::throwLogarithmZeroBase();	
			if (b.im == 0)
				return ComplexNumber<T>(log(b.re));
			ComplexNumber<T> a(e<T>());
			return ComplexNumber<T>(log(module(b)), argument(b)) / ComplexNumber<T>(log(module(a)), argument(a));
		}

		template <class T>
		static Matrix<T> logarithm10(const Matrix<T> &b)
		{
			Matrix<T> C(b.M, b.N);
			for (int i = 0; i < b.M; i++)
				for (int j = 0; j < b.N; j++)
					C.mx[i][j] = logarithm10(b.mx[i][j]);
			return C;
		}

		template <class T>
		static ComplexNumber<T> logarithm10(const ComplexNumber<T> &b)
		{
			if (b.im == 0)
				return ComplexNumber<T>(log10(b.re));
			return logarithm(ComplexNumber<T>(10), b);
		}

		template <class T>
		static Matrix<T> logarithm2(const Matrix<T> &b)
		{
			Matrix<T> C(b.M, b.N);
			for (int i = 0; i < b.M; i++)
				for (int j = 0; j < b.N; j++)
					C.mx[i][j] = logarithm2(b.mx[i][j]);
			return C;
		}

		template <class T>
		static ComplexNumber<T> logarithm2(const ComplexNumber<T> &b)
		{
			return logarithm(ComplexNumber<T>(2), b);
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

		template <class T>
		static ComplexNumber<T> sinus(const ComplexNumber<T> &z)
		{
			if (z.im == 0)
				return ComplexNumber<T>(sin(z.re));
			return ComplexNumber<T>(sin(z.re)*cosh(z.im), cos(z.re)*sinh(z.im));
		}

		template <class T>
		static Matrix<T> sinus(const Matrix<T> &m)
		{
			Matrix<T> out(m.M, m.N);
			for (int i = 0; i < m.M; i++)
				for (int j = 0; j < m.N; j++)
					out.mx[i][j] = sinus(m.mx[i][j]);
			return out;
		}
	
		template <class T>
		static ComplexNumber<T> cosinus(const ComplexNumber<T> &a)
		{
			if (a.im == 0)
				return ComplexNumber<T>(cos(a.re));
			int m = a.im>0 ? 1 : -1;
			return ComplexNumber<T>(cos(a.re)*cosh(a.im), sin(a.re)*sinh(a.im)*m);
		}

		template <class T>
		static Matrix<T> cosinus(const Matrix<T> &a)
		{
			Matrix<T> c(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					c.mx[i][j] = cosinus(a.mx[i][j]);
			return c;
		}

		template <class T>
		static ComplexNumber<T> tangens(const ComplexNumber<T> &a)
		{
			if (a.im == 0)
				return ComplexNumber<T>(tan(a.re));
			int m = a.im>0 ? 1 : -1;
			ComplexNumber<T> out;
			out.re = out.im = 1 / (cos(2 * a.re) + cosh(2 * a.im));
			out.re *= sin(2 * a.re);
			out.im *= sinh(2 * a.im);
			return out;
		}

		template <class T>
		static Matrix<T> tangens(const Matrix<T> &a)
		{
			Matrix<T> c(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					c.mx[i][j] = tangens(a.mx[i][j]);
			return c;
		}

	};
}

