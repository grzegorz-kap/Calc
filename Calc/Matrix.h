#pragma once

#include "export.h"

#include <vector>
#include <memory>

#include "ComplexNumber.h"
#include "Data.h"

using std::vector;
using std::shared_ptr;

namespace PR
{

	template<class T> class  Matrix
	{
		
	protected:
		vector< vector< ComplexNumber<T> >> mx;
		int M;
		int N;
	public:
		friend class MatrixTransposer;
		Matrix()
			:M(0),N(0)
		{
		};

		
		Matrix(Matrix<T> &&other)
			:M(0), N(0)
		{
			*this = std::move(other);
		}

		Matrix<T> & operator = (Matrix<T> &&other)
		{
			if (this != &other)
			{
				mx = std::move(other.mx);
				M = other.M;
				N = other.N;
				other.M = 0;
				other.N = 0;

			}
			return *this;
		}

		Matrix(const string &scalar)
			:Matrix()
		{
			mx.push_back(vector<ComplexNumber<T>>(1));
			mx[0][0] = ComplexNumber<T>(scalar);
			M = N = 1;
		}

		Matrix(int m, int n)
			: Matrix()
		{ 
			M = m;
			N = n;
			mx.assign(m, vector<ComplexNumber<T>>(n)); 
		}

		Matrix(int m, int n, const ComplexNumber<T> &value)
		{ 
			M = m;
			N = n;
			mx.assign(m, vector<ComplexNumber<T>>(n, value)); 
		}

		Matrix(int m, int n, T re, T im = 0.0)
		{
			M = m;
			N = n;
			mx.assign(m, vector<ComplexNumber<T>>(n, ComplexNumber<T>(re, im)));
		}

		~Matrix()
		{
		};

		template <class U>
		Matrix<T> div_t(const Matrix<U> &b) const
		{
			if (b.M == 1 && b.N == 1)
				return *this / b.mx[0][0];
			else if (M == 1 && N == 1)
				return b.div(mx[0][0]);

			Matrix<T> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] / b.mx[i][j];
			return C;
		}

		template <class U>
		Matrix<T> mult_t(const Matrix<U> &b) const
		{
			if (b.M == 1 && b.N == 1)
				return *this * b.mx[0][0];
			else if (M == 1 && N == 1)
				return b * mx[0][0];

			if (b.N != N || b.M != M)
				throw CalcException("Incompatibile matrix m x n");
			Matrix<T> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] + b.mx[i][j];
			return C;
		}

		void rows(int arg){ M = arg; }

		void cols(int arg){ N = arg; }

		int rows() const 
		{ 
			return mx.size(); 
		}

		int cols() const
		{
			if (mx.size() > 0)
				return (int)mx[0].size();
			else
				return 0;
		}

		Matrix<T>  neg()
		{
			Matrix<T> out(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					out.mx[i][j] = -mx[i][j];
			return out;
		}

		template <class U>
		Matrix<T> operator + (const Matrix<U> &B) const
		{
			if (B.M == 1 && B.N == 1)
				return *this+B.mx[0][0];
			else if (M == 1 && N == 1)
				return B+mx[0][0];

			Matrix<T> C(M,N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] + B.mx[i][j];
			return C;
		}


		template <class U>
		Matrix<T> operator + (const ComplexNumber<U> &b) const
		{
			Matrix<T> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] + b;
			return C;
		}

		template <class U>
		Matrix<T> operator - (const Matrix<U> &B) const
		{
			if (B.M == 1 && B.N == 1)
				return *this - B.mx[0][0];
			else if (M == 1 && N == 1)
				return B.sub(mx[0][0]);

			Matrix<T> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] - B.mx[i][j];
			return C;
		}

		template <class U>
		Matrix<T> sub(const ComplexNumber<U> &b) const
		{
			Matrix<T> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = b - mx[i][j];
			return C;
		}

		template <class U>
		Matrix<T> operator - (const ComplexNumber<U> &b) const
		{
			Matrix<T> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] - b;
			return C;
		}

		template <class U>
		Matrix<T> operator * (const Matrix<U> &B) const
		{
			if (B.M == 1 && B.N == 1)
				return *this * B.mx[0][0];
			else if (M == 1 && N == 1)
				return B * mx[0][0];

			Matrix<T> C(M, B.N);
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < B.N; j++)
				{
					ComplexNumber<T> temp(0.0, 0.0);
					for (int k = 0; k < N; k++)
						temp += mx[i][k] * B.mx[k][j];
					C.mx[i][j] = temp;
				}
			}
			return C;
		}

		template <class U>
		Matrix<T> operator * (const ComplexNumber<U> &b) const
		{
			Matrix<T> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] * b;
			return C;
		}

		template <class U>
		Matrix<T> operator / (const Matrix<U> &B) const
		{
			if (B.M == 1 && B.N == 1)
				return *this / B.mx[0][0];
			else if (M == 1 && N == 1)
				return B.div(mx[0][0]);
		}

		template <class U>
		Matrix<T> div(const ComplexNumber<U> &b) const
		{
			Matrix<T> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = b / mx[i][j];
			return C;
		}

		template <class U>
		Matrix<T> operator / (const ComplexNumber<U> &b) const
		{
			Matrix<T> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] / b;
			return C;
		}

		ComplexNumber<T>& operator()(int i, int j)
		{ 
			return mx[i][j]; 
		}

		vector<vector<ComplexNumber<T>>>* getVector(){ return &mx; }

		int * getM_P(){ return &M; }
		int * getN_P(){ return &N; }

		string toString() const
		{
			string temp = "";
			for (int i = 0; i < M; i++)
			{
				temp.append("\n");
				for (int j = 0; j < N; j++)
					temp.append("\t" + mx[i][j].toString());
			}
			return temp;
		}
	};
}

template class PR::Matrix < float > ;
template class PR::Matrix < int > ;
template class PR::Matrix < double > ;