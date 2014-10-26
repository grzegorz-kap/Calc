#pragma once

#include <cmath>

#include "Matrix.h"

using std::pow;

#include <boost/math/constants/constants.hpp>

namespace PR
{

	template <class X>
	class Matrix;

	template <class X>
	class ComplexNumber;

	class Math
	{
	public:
		Math() = delete;
		~Math() = delete;

		/* Element wise exponentiation */
		template<class T, class U>
		static auto power(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (b.isScalar())
				return Math::power(a, b.mx[0][0]);

			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < C.M; i++)
			{
				for (int j = 0; j < C.N; j++)
					C.mx[i][j] = Math::power(a.mx[i][j], b.mx[i][j]);
			}
			return C;
		}

		template<class T>
		static auto power(const cpp_bin_float_100 &a, const cpp_bin_float_100 &b)
			-> ComplexNumber < T >
		{
			return ComplexNumber<T>(std::pow(a.convert_to<double>(), b.convert_to<double>()));
		}
		
		template<class T>
		static auto power(const double &a, const double &b)
			->ComplexNumber<T>
		{
			return ComplexNumber<T>(std::pow(a, b));
		}
		
		template<class T,class U>
		static auto power(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			if (a.im == 0 && b.im == 0)
				return ComplexNumber<decltype(T() + U())>(Math::power<T>(a.re, b.re));
			
			ComplexNumber<T> e(boost::math::constants::e<T>());
			auto y = b*logarithm(e, a);
			ComplexNumber<T> out;
			out.re = out.im = pow(e.re, y.re);
			out.re = out.re*cos(y.im);
			out.im = out.im*sin(y.im);
			return out;
		}

		template <class T,class U>
		static auto power(const Matrix<T> &a, const ComplexNumber<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					C.mx[i][j] = Math::power(a.mx[i][j], b);
			return C;
		}

		template <class T,class U>
		static auto power(const ComplexNumber<T> &a, const Matrix<U> &b)
			->ComplexNumber < decltype(T() + U()) >
		{
			if (!b.isScalar())
				throw "!";
			
			return power(a, b.mx[0][0]);
		}

		/* Matrix exponentiation */
		template<class T,class U>
		static auto mpower(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (a.isScalar() && b.isScalar())
				return Math::power(a.mx[0][0], b.mx[0][0]);
			
			throw CalcException("Matrix ^ Matrix to be implemented in the feature!");
		}

		template <class T, class U>
		static auto mpower(const Matrix<T> &a, const ComplexNumber<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					C.mx[i][j] = Math::power(mx[i][j], b);
			return C;
		}

		template <class T, class U>
		static auto mpower(const ComplexNumber<T> &a, const Matrix<U> &b)
			->ComplexNumber < decltype(T() + U()) >
		{
			if (!b.isScalar())
				throw "!";

			return Math::power(a, b.mx[0][0]);
		}

		template<class T, class U>
		static auto mpower(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			return power(a, b);
		}

	private:

		/* Element wise exponentiation by scalar */
		template<class T,class U>
		static auto power(const Matrix<T> &a, const U &b)
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < C.M; i++)
			{
				for (int j = 0; j < C.N; j++)
					C.mx[i][j] = Math::power(a.mx[i][j], b);
			}
			return C;
		}

		template<class T,class U>
		static auto pow_by_squaring(const Matrix<T> &a, const U & n)
			->Matrix<decltype(T()+U())>
		{
			if (n < 0)
				//return Math::pow_by_squaring(1 / a, -n);
				throw CalcException("To implement pow_by_squaring!");
			else if (n == 0)
				throw CalcException("To implement pow_by_squaring!");
			else if (n == 1)
				return a;
			else if (n % 2 == 0)
				return pow_by_squaring(a*a, n / 2);
			else if (n % 2 != 0)
				return a*pow_by_squaring(a*a, (n - 1) / 2);
			throw CalcException("!");
		}


	public:
		template <class T,class U>
		static auto logarithm(const ComplexNumber<T> &a,const ComplexNumber<U> &b )
			->ComplexNumber<decltype(T() + U())>
		{
			if (a.re == 0 && a.im == 0)
				NumericException::throwLogarithmZeroBase();
			if (b.re == 0 && b.im == 0)
				NumericException::throwLogarithmFromZero();

			if (a.im == 0 && b.im == 0)
				return ComplexNumber<decltype(T() + U())>(log(b.re)/log(a.re));

			return ComplexNumber<decltype(T() + U())>(log(module(b)), argument(b))/ComplexNumber<decltype(T() + U())> (log(module(a)), argument(a));
		}

		/* Argument of complex number */
		template <class T>
		static T argument(const ComplexNumber<T> &z)
		{
			if (z.re > 0)
				return atan(z.im / z.re);
			if (z.re < 0)
				return atan(z.im / z.re) + boost::math::constants::pi<T>();
			if (z.im>0)
				return 0.5*boost::math::constants::pi<T>();
			if (z.im < 0)
				return -0.5*boost::math::constants::pi<T>();
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

