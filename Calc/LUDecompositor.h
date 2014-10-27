#pragma once

#include "Matrix.h"
#include "Mathematic.h"

namespace PR
{
	class LUDecompositor
	{
		LUDecompositor() =delete;
		~LUDecompositor()=delete;

	public:

		template<class T>
		static Matrix<T> lu(const Matrix<T> &b);

		template <class T>
		static ComplexNumber<T> lu(const ComplexNumber<T> &a)
		{
			return a;
		}
	};

}
