#pragma once

#include "Matrix.h"
#include "MatrixBuilder.h"
#include "Mathematic.h"

#include <memory>

namespace PR
{
	class MatrixUtils
	{
		MatrixUtils() =delete;
		~MatrixUtils()=delete;

	public:

		template<class T>
		static int lu(const Matrix<T> &src, Matrix<T> **L, Matrix<T> **U = nullptr, Matrix<T> **P=nullptr);

		template <class T>
		static int lu(const ComplexNumber<T> &src, ComplexNumber<T> **L, ComplexNumber<T> **U = nullptr, ComplexNumber<T> **P = nullptr);

		template <class T>
		static ComplexNumber<T> det(const Matrix<T> &a);

		template <class T>
		static ComplexNumber<T> det(const ComplexNumber<T> &a){ return a; }

		template <class T>
		static ComplexNumber<T> inv(const ComplexNumber<T> &a){ return ComplexNumber<T>(1) / a; }

		template <class T>
		static Matrix<T> inv(const Matrix<T> &A);

		template <class T>
		static Matrix<T> divide(const Matrix<T> &AA, const Matrix<T> &BB)
		{
			return AA * inv(BB);
		}
		

		template <class T> 
		static void url(const Matrix<T> &A, const Matrix<T> &b, int j_b, Matrix<T> &x,int j_x)
		{
			x.mx[0][j_x] = b.mx[0][j_b];
			for (int i = 1; i < A.M; i++)
			{
				ComplexNumber<T> sum(0);
				for (int j = 0; j < i ; j++)
					sum += A.mx[i][j] * x.mx[j][j_x];
				x.mx[i][j_x] = b.mx[i][j_b] - sum;
			}

			x.mx.back()[j_x] /= A.mx.back().back();
			for (int i = A.M - 2; i >= 0; i--)
			{
				ComplexNumber<T> sum(0);
				for (int j = i + 1; j < A.M;j++)
					sum += A.mx[i][j] * x.mx[j][j_x];
				x.mx[i][j_x] -= sum;
				x.mx[i][j_x] /= A.mx[i][i];
			}
		}
	};

}
