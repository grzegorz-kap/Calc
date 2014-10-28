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
		static void lu(const Matrix<T> &b, Matrix<T> **, Matrix<T> **ptr1 = nullptr, Matrix<T> **ptr2=nullptr);

		template <class T>
		static void lu(const ComplexNumber<T> &a, ComplexNumber<T> **ptr, 
			ComplexNumber<T> **ptr1 = nullptr, ComplexNumber<T> **ptr2=nullptr)
		{
			*ptr = new ComplexNumber<T>(a);
			if (ptr1) *ptr1= new ComplexNumber<T>(a);
			if (ptr2) *ptr2 = new ComplexNumber<T>(1);
		}
	};

}
