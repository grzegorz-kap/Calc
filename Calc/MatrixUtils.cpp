#include "stdafx.h"
#include "MatrixUtils.h"

namespace PR
{
	/* Set pointers to function for matrix division */
	decltype(Matrix<double>::matrix_divide) Matrix<double>::matrix_divide = MatrixUtils::divide<double>;
	decltype(Matrix<hdouble>::matrix_divide) Matrix<hdouble>::matrix_divide = MatrixUtils::divide<hdouble>;

	template <class T>
	int MatrixUtils::lu(const Matrix<T> &a,Matrix<T> **l,Matrix<T> **u,Matrix<T> **p)
	{
		if (a.M != a.N)
			NumericException::throwLuNotSquare();

		vector<int> s;
		vector<int> d;

		int swaps_count = 0;

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
				++swaps_count;
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
		return swaps_count;
	}

	template <class T>
	int MatrixUtils::lu(const ComplexNumber<T> &src, ComplexNumber<T> **L,ComplexNumber<T> **U, ComplexNumber<T> **P)
	{
		*L = new ComplexNumber<T>(src);
		if (U) *U = new ComplexNumber<T>(src);
		if (P) *P = new ComplexNumber<T>(1);
		return 0;
	}
	
	template <class T>
	ComplexNumber<T> MatrixUtils::det(const Matrix<T> &a)
	{
		if (a.M != a.N)
			throw NumericException("Cannot compute determinant from not squere matrix");
		if (a.M == 0)
			return ComplexNumber<T>(1);

		Matrix<T> *ptr = nullptr;
		bool sign = lu(a, &ptr) % 2 ? true : false;
		auto &mx = ptr->mx;
		ComplexNumber<T> det = mx[0][0];
		for (int i = 1; i < a.M; i++)
			det *= mx[i][i];
		SafeRealase(&ptr);
		if (sign)
			return det.neg();
		else
			return det;
	}

	template <class T>
	Matrix<T> MatrixUtils::inv(const Matrix<T> &A)
	{
		Matrix<T> *lu = nullptr;
		Matrix<T> *eye = nullptr;
		
		MatrixUtils::lu(A, &lu, (Matrix<T>**)nullptr, &eye);
		Matrix<T> &x = *eye;
		Matrix<T> &a = *lu;

		unique_ptr<Matrix<T>> x_deleter(eye);

		for (int j = 0; j < x.N; j++)
		{
			url(a, x, j, x, j);
		}
		SafeRealase(&lu);
		return x;
	}

	template <class T> 
	ComplexNumber<T> MatrixUtils::det(const ComplexNumber<T> &a)
	{ 
		return a; 
	}

	template <class T> 
	ComplexNumber<T> MatrixUtils::inv(const ComplexNumber<T> &a)
	{ 
		return ComplexNumber<T>(1) / a; 
	}

	template <class T>
	Matrix<T> MatrixUtils::divide(const Matrix<T> &AA, const Matrix<T> &BB)
	{
		return AA * inv(BB);
	}

	template <class T>
	void MatrixUtils::url(const Matrix<T> &A, const Matrix<T> &b, int j_b, Matrix<T> &x, int j_x)
	{
		x.mx[0][j_x] = b.mx[0][j_b];
		for (int i = 1; i < A.M; i++)
		{
			ComplexNumber<T> sum(0);
			for (int j = 0; j < i; j++)
				sum += A.mx[i][j] * x.mx[j][j_x];
			x.mx[i][j_x] = b.mx[i][j_b] - sum;
		}

		x.mx.back()[j_x] /= A.mx.back().back();
		for (int i = A.M - 2; i >= 0; i--)
		{
			ComplexNumber<T> sum(0);
			for (int j = i + 1; j < A.M; j++)
				sum += A.mx[i][j] * x.mx[j][j_x];
			x.mx[i][j_x] -= sum;
			x.mx[i][j_x] /= A.mx[i][i];
		}
	}

	/* Necessary for definitions in cpp file */
	template int MatrixUtils::lu(const Matrix<double> &, Matrix<double>**, Matrix<double>**, Matrix<double>**);
	template int MatrixUtils::lu(const Matrix<hdouble> &, Matrix<hdouble>**, Matrix<hdouble>**, Matrix<hdouble>**);
	template int MatrixUtils::lu(const ComplexNumber<double> &, ComplexNumber<double>**, ComplexNumber<double>**, ComplexNumber<double>**);
	template int MatrixUtils::lu(const ComplexNumber<hdouble> &, ComplexNumber<hdouble>**, ComplexNumber<hdouble>**, ComplexNumber<hdouble>**);
	
	template ComplexNumber<double> MatrixUtils::det(const Matrix<double>&);
	template ComplexNumber<hdouble> MatrixUtils::det(const Matrix<hdouble>&);
	template ComplexNumber<double> MatrixUtils::det(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> MatrixUtils::det(const ComplexNumber<hdouble>&);
	
	template ComplexNumber<double> MatrixUtils::inv(const ComplexNumber<double>&);
	template ComplexNumber<hdouble> MatrixUtils::inv(const ComplexNumber<hdouble>&);
	template Matrix<double> MatrixUtils::inv(const Matrix<double> &);
	template Matrix<hdouble> MatrixUtils::inv(const Matrix<hdouble> &);

	template Matrix<double> MatrixUtils::divide(const Matrix<double>&, const Matrix<double>&);
	template Matrix<hdouble> MatrixUtils::divide(const Matrix<hdouble>&, const Matrix<hdouble>&);

	template void MatrixUtils::url(const Matrix<double>&, const Matrix<double>&, int, Matrix<double>&, int);
	template void MatrixUtils::url(const Matrix<hdouble>&, const Matrix<hdouble>&, int, Matrix<hdouble>&, int);
}