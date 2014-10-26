#pragma once

#include <cmath>

#include "Matrix.h"

#include <boost\multiprecision\cpp_bin_float.hpp>

using namespace boost::multiprecision;


namespace PR
{
	template <class X>
	class Matrix;

	template <class X>
	class ComplexNumber;

	class Power
	{
	public:
		Power() = delete;
		~Power() = delete;

		/* Element wise exponentiation */
		template<class T, class U>
		static auto pow(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (b.isScalar())
				return Power::pow(a, b.mx[0][0]);

			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < C.M; i++)
			{
				for (int j = 0; j < C.N; j++)
					C.mx[i][j] = Power::pow(a.mx[i][j], b.mx[i][j]);
			}
			return C;
		}

		template<class T>
		static auto pow(const cpp_bin_float_100 &a, const cpp_bin_float_100 &b)
			-> ComplexNumber < T >
		{
			return ComplexNumber<T>(std::pow(a.convert_to<double>(), b.convert_to<double>()));
		}
		template<class T>
		static auto pow(const double &a, const double &b)
			->ComplexNumber<T>
		{
			return ComplexNumber<T>(std::pow(a, b));
		}
		
		template<class T,class U>
		static auto pow(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			if (a.im == 0 && b.im == 0)
				return ComplexNumber<decltype(T() + U())>(Power::pow<T>(a.re,b.re));
			else
				throw "C";
		}

		template <class T,class U>
		static auto pow(const Matrix<T> &a, const ComplexNumber<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					C.mx[i][j] = Power::pow(a.mx[i][j], b);
			return C;
		}

		template <class T,class U>
		static auto pow(const ComplexNumber<T> &a, const Matrix<U> &b)
			->ComplexNumber < decltype(T() + U()) >
		{
			if (!b.isScalar())
				throw "!";
			
			return pow(a, b.mx[0][0]);
		}

		/* Matrix exponentiation */
		template<class T,class U>
		static auto mpow(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (a.isScalar() && b.isScalar())
				return Power::pow(a.mx[0][0], b.mx[0][0]);
			
			throw "!";
		}

		template <class T, class U>
		static auto mpow(const Matrix<T> &a, const ComplexNumber<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					C.mx[i][j] = Power::pow(mx[i][j], b);
			return C;
		}

		template <class T, class U>
		static auto mpow(const ComplexNumber<T> &a, const Matrix<U> &b)
			->ComplexNumber < decltype(T() + U()) >
		{
			if (!b.isScalar())
				throw "!";

			return Power::pow(a, b.mx[0][0]);
		}

		template<class T, class U>
		static auto mpow(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			if (a.im == 0 && b.im == 0)
				return ComplexNumber<decltype(T() + U())>(pow<T>(a.re , b.re));
			else
				throw "C";
		}

	private:

		/* Element wise exponentiation by scalar */
		template<class T,class U>
		static auto pow(const Matrix<T> &a, const U &b)
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < C.M; i++)
			{
				for (int j = 0; j < C.N; j++)
					C.mx[i][j] = Power::pow(a.mx[i][j], b);
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
	};
}

