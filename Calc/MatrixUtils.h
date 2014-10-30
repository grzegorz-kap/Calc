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

		template <class T> static ComplexNumber<T> det(const Matrix<T> &a);
		template <class T> static ComplexNumber<T> det(const ComplexNumber<T> &a);
		template <class T> static ComplexNumber<T> inv(const ComplexNumber<T> &a);
		template <class T> static Matrix<T> inv(const Matrix<T> &A);

		template <class T> static Matrix<T> divide(const Matrix<T> &AA, const Matrix<T> &BB);
		template <class T> static void url(const Matrix<T> &A, const Matrix<T> &b, int j_b, Matrix<T> &x, int j_x);
	};

}