#pragma once

#include "Matrix.h"
#include "MatrixBuilder.h"
#include "Mathematic.h"

#include <memory>

namespace PR
{
	class LUDecompositor
	{
		LUDecompositor() =delete;
		~LUDecompositor()=delete;

	public:

		template<class T>
		static int lu(const Matrix<T> &src, Matrix<T> **L, Matrix<T> **U = nullptr, Matrix<T> **P=nullptr);

		template <class T>
		static int lu(const ComplexNumber<T> &src, ComplexNumber<T> **L, 
			ComplexNumber<T> **U = nullptr, ComplexNumber<T> **P=nullptr)
		{
			*L = new ComplexNumber<T>(src);
			if (U) *U= new ComplexNumber<T>(src);
			if (P) *P = new ComplexNumber<T>(1);
			return 0;
		}
	};

}
