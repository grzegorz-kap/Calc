#pragma once

#include <cmath>

#include "Value.h"
#include "Matrix.h"

namespace PR
{
	template<class X>
	class Value;

	template <class X>
	class Matrix;

	class Math
	{
	public:
		Math() = delete;
		~Math() = delete;

		/* Value exponentiation */
		template<class T,class U>
		static auto pow(const Value<T> &a, const Value<U> &b)
			->Value < decltype(T() + U()) >
		{
			return Value<decltype(T() + U())>(std::pow(a.value,b.value));
		}

		template<class T,class U>
		static auto pow(const T& a, const U& b)
			-> decltype(T() + U())
		{
			return std::pow(a, b);
		}

		/* Element wise exponentiation */
		template<class T, class U>
		static auto pow(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (b.isScalar())
				return Math::pow(a, b.mx[0][0]);

			Matrix<decltype(T() + U())> C(a.M, a.N);
			for (int i = 0; i < C.M; i++)
			{
				for (int j = 0; j < C.N; j++)
					C.mx[i][j] = pow(a.mx[i][j], b.mx[i][j]);
			}
			return C;
		}

		/* Matrix exponentiation */
		template<class T,class U>
		static auto mpow(const Matrix<T> &a, const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (a.isScalar() && b.isScalar())
				return Math::pow(a.mx[0][0], b.mx[0][0]);
			
			if (b.isScalar())
			{
				return pow_by_squaring<T>(a, (int)b.mx[0][0]);
			}
		}

		template<class T, class U>
		static auto mpow(const Value<T> &a, const Value<U> &b)
			->Value < decltype(T() + U()) >
		{
			return Math::pow(a, b);
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
				throw CalcException("To implement!");
			else if (n == 0)
				throw CalcException("To implement!");
			else if (n == 1)
				return a;
			else if (n % 2 == 0)
				return Math::pow_by_squaring(a*a, n / 2);
			else if (n % 2 != 0)
				return a*Math::pow_by_squaring(a*a, (n - 1) / 2);
		}
	};
}

