#include "stdafx.h"
#include "LUDecompositor.h"

namespace PR
{
	template <class T>
	int LUDecompositor::lu(const Matrix<T> &a,Matrix<T> **l,Matrix<T> **u,Matrix<T> **p)
	{
		if (a.M != a.N)
			NumericException::throwLuNotSquare();

		vector<int> s;
		vector<int> d;

		/*Doolittle-Crout*/
		std::unique_ptr<Matrix<T>> i_l = std::make_unique<Matrix<T>>(a);
		std::unique_ptr<Matrix<T>> i_p;
		Matrix<T> &A = *i_l;
		int m = A.M;
		int n = A.N;

		if (p)
		{
			if (*p == nullptr)
				i_p = make_unique<Matrix<T>>(MatrixBuilder<T>::buildEye(a.M, a.N));
			else
				i_p.reset(*p);
			if (i_p->rows() != a.M)
				throw CalcException("LU decompositor permutation matrix has wrong rows count");
		}

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
			{
				std::swap(A.mx[k], A.mx[idx]);
				if (p)
					std::swap(i_p->mx[k], i_p->mx[idx]);
				else if (u)
				{
					s.push_back(k);
					d.push_back(idx);
				}
			}

			ComplexNumber<T> &ref = A.mx[k][k];
			for (int j = k + 1; j < n; j++)
				A.mx[j][k] /= ref;

			for (int i = k + 1; i < m; i++)
				for (int j = k + 1; j < n; j++)
					if (i != k)
						A.mx[i][j] -= A.mx[i][k] * A.mx[k][j];	
		}
		Matrix<T> *n_u =nullptr;
		if (u)
		{
			n_u = new Matrix<T>(m, n);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
				{
				if (i == j){ n_u->mx[i][j] = std::move(A.mx[i][j]); A.mx[i][j] = ComplexNumber<T>(1); }
				else if (i < j){ n_u->mx[i][j] = std::move(A.mx[i][j]); A.mx[i][j] = ComplexNumber<T>(0); }
				else { n_u->mx[i][j] = ComplexNumber<T>(0); }
				}
		}

		if (u&&!p)
		{
			for (int i = s.size()-1; i >=0; i--)
				std::swap(A.mx[s[i]], A.mx[d[i]]);
		}

		*l = i_l.release();
		if (p)
			*p = i_p.release();
		if (u)
			*u = n_u;
		return d.size();
	}

	template int LUDecompositor::lu(const Matrix<double> &, Matrix<double>**, Matrix<double>**, Matrix<double>**);
	template int LUDecompositor::lu(const Matrix<hdouble> &, Matrix<hdouble>**, Matrix<hdouble>**, Matrix<hdouble>**);
}