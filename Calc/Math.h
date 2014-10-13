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

	private:

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
	};
}

