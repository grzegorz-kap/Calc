#pragma once

#include <cmath>

#include "Matrix.h"




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
				return pow(a, b.mx[0][0]);

			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < C.M; i++)
			{
				for (int j = 0; j < C.N; j++)
					C.mx[i][j] = pow(a.mx[i][j], b.mx[i][j]);
			}
			return C;
		}

		template<class T,class U>
		static auto pow(const T& a, const U& b)
			-> decltype(T() + U())
		{
			return std::pow(a, b);
		}
		
		template<class T,class U>
		static auto pow(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			if (a.im == 0 && b.im == 0)
				return ComplexNumber<decltype(T() + U())>(pow(a.re , b.re));
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
					C.mx[i][j] = pow(a.mx[i][j], b);
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
				return pow(a.mx[0][0], b.mx[0][0]);
			
			throw "!";
		}

		template <class T, class U>
		static auto mpow(const Matrix<T> &a, const ComplexNumber<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < a.M; i++)
				for (int j = 0; j < a.N; j++)
					C.mx[i][j] = pow(mx[i][j], b);
			return C;
		}

		template <class T, class U>
		static auto mpow(const ComplexNumber<T> &a, const Matrix<U> &b)
			->ComplexNumber < decltype(T() + U()) >
		{
			if (!b.isScalar())
				throw "!";

			return pow(a, b.mx[0][0]);
		}

		template<class T, class U>
		static auto mpow(const ComplexNumber<T> &a, const ComplexNumber<U> &b)
			->ComplexNumber<decltype(T() + U())>
		{
			if (a.im == 0 && b.im == 0)
				return ComplexNumber<decltype(T() + U())>(pow(a.re , b.re));
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
					C.mx[i][j] = pow(a.mx[i][j], b);
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

