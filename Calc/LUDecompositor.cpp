#include "stdafx.h"
#include "LUDecompositor.h"

namespace PR
{
	template <class T>
	Matrix<T> LUDecompositor::lu(const Matrix<T> &a)
	{
		if (a.M != a.N)
			NumericException::throwLuNotSquare();

		/*Doolittle-Crout*/
		Matrix<T> A = a;
		int m = A.M;
		int n = A.N;

		for (int k = 0; k < m - 1; k++)
		{
			/*Finding max module*/
			T max = 0;
			int idx = k;
			for (int i = k; i < m; i++)
			{
				T module = Mathematic::module(A.mx[i][k]);
				if (module>max)
				{
					max = module;
					idx = i;
				}
			}

			/* Swap vectors if neccessary */
			if (k != idx)
				A.mx[k].swap(A.mx[idx]);

			for (int j = k + 1; j < n; j++)
				A.mx[j][k] = A.mx[j][k] / A.mx[k][k];

			for (int i = k + 1; i < m; i++)
				for (int j = k + 1; j < n; j++)
					if (i != k)
						A.mx[i][j] = A.mx[i][j] - A.mx[i][k] * A.mx[k][j];
			return A;
		}
	}

	template Matrix<double> LUDecompositor::lu(const Matrix<double> &);
	template Matrix<hdouble> LUDecompositor::lu(const Matrix<hdouble> &);
}