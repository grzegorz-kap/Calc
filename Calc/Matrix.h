#pragma once

#include <vector>
#include <memory>

#include "ComplexNumber.h"
#include "functions.h"

using std::vector;
using std::shared_ptr;

namespace PR
{
	template <class T>
	class ComplexNumber;
	class Power;

	template<class T> class  Matrix
		: public Numeric<Matrix<T>>
	{
		
	protected:
		vector< vector< ComplexNumber<T> >> mx;
		int M;
		int N;
	public:
		friend class MatrixTransposer;
		friend class Power;
		
		Matrix()
			:M(0),N(0)
		{
			_type = Data::find_type(typeid(*this));
		};

		Matrix(const ComplexNumber<T> &b)
			:Matrix(1,1,b)
		{
			_type = Data::find_type(typeid(*this));
		}
		
		Matrix(Matrix<T> &&other)
			:M(0), N(0)
		{
			*this = std::move(other);
			_type = Data::find_type(typeid(*this));
		}

		Matrix(const Matrix<T> &b)
			:mx(b.mx), M(b.M), N(b.N)
		{
			_type = Data::find_type(typeid(*this));
		}

		Matrix(const string &scalar)
			:Matrix()
		{
			mx.push_back(vector<ComplexNumber<T>>(1));
			mx[0][0] = (T)atof(scalar.c_str());
			M = N = 1;
			_type = Data::find_type(typeid(*this));
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
			_type = Data::find_type(typeid(*this));
			mx.assign(m, vector<ComplexNumber<T>>(n, value));
		}

		virtual ~Matrix()
		{
		};

		Matrix<T> & operator = (const Matrix<T> &b)
		{
			if (this != &b)
			{
				mx = b.mx;
				M = b.M;
				N = b.N;
			}
			return *this;
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

		

		/* Right array division */
		template <class U>
		auto rdivide(const Matrix<U> &b) const
			-> Matrix<decltype(T() + U())>
		{
			if (b.M == 1 && b.N == 1)
				return *this / b.mx[0][0];
			else if (M == 1 && N == 1)
				return b.ldivide(mx[0][0]);

			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] / b.mx[i][j];
			return C;
		}


		/* Divide b by matrix */
		template <class U>
		auto ldivide(const ComplexNumber<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = b / mx[i][j];
			return C;
		}

		/* Divide matrix by b */
		template <class U>
		auto rdivide(const ComplexNumber<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] / b;
			return C;
		}

		/* Element wise multiplication */
		template <class U>
		auto times(const Matrix<U> &b) const
			-> Matrix<decltype(T() + U())>
		{
			if (b.M == 1 && b.N == 1)
				return *this * b.mx[0][0];
			else if (M == 1 && N == 1)
				return b * mx[0][0];

			if (b.N != N || b.M != M)
				throw CalcException("Incompatibile matrix m x n");
			Matrix<decltype(T() + U())> C(M, N);
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

		Matrix<T> neg () const
		{
			Matrix<T> out(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					out.mx[i][j] = mx[i][j].neg();
			return out;
		}

		template <class U>
		auto operator + (const Matrix<U> &B) const
			-> Matrix<decltype(T() + U())>
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
		auto operator + (const ComplexNumber<U> &b) const
			-> Matrix<decltype(T() + U())>
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] + b;
			return C;
		}

		template <class U>
		auto operator - (const Matrix<U> &B) const
			-> Matrix<decltype(T() + U())>
		{
			if (B.M == 1 && B.N == 1)
				return *this - B.mx[0][0];
			else if (M == 1 && N == 1)
				return B.sub(mx[0][0]);

			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] - B.mx[i][j];
			return C;
		}

		template <class U>
		auto sub(const ComplexNumber<U> &b) const
			-> Matrix<decltype(T() + U())>
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = b - mx[i][j];
			return C;
		}

		template <class U>
		auto operator - (const ComplexNumber<U> &b) const
			-> Matrix<decltype(T() + U())>
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] - b;
			return C;
		}

		template <class U>
		auto operator * (const Matrix<U> &B) const
			-> Matrix<decltype(T() + U())>
		{
			if (B.M == 1 && B.N == 1)
				return *this * B.mx[0][0];
			else if (M == 1 && N == 1)
				return B * mx[0][0];

			Matrix<decltype(T() + U())> C(M, B.N);
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < B.N; j++)
				{
					ComplexNumber<T> temp(0.0);
					for (int k = 0; k < N; k++)
						temp += mx[i][k] * B.mx[k][j];
					C.mx[i][j] = temp;
				}
			}
			return C;
		}

		template <class U>
		auto operator * (const ComplexNumber<U> &b) const
			->Matrix<decltype(T() + U())>
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] * b;
			return C;
		}

		template <class U>
		auto operator / (const Matrix<U> &B) const
			->Matrix < decltype(T() / U()) >
		{
			if (B.M == 1 && B.N == 1)
				return *this / B.mx[0][0];
			else if (M == 1 && N == 1)
				return B.ldivide(mx[0][0]);
		}

		template <class U>
		auto operator / (const ComplexNumber<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T()+U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] / b;
			return C;
		}

		T& operator()(int i, int j)
		{ 
			return mx[i][j]; 
		}

		/* Eq operator */
		template<class U>
		auto operator == (const Matrix<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			if (isScalar())
				return b == mx[0][0];
			if (b.isScalar())
				return *this == b.mx[0][0];

			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] == b.mx[i][j];
			return C;
		}

		template <class U>
		auto operator == (const ComplexNumber<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] == b;
			return C;
		}

		template<class U>
		auto operator != (const Matrix<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			if (isScalar())
				return b != mx[0][0];
			if (b.isScalar())
				return *this != b.mx[0][0];

			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] != b.mx[i][j];
			return C;
		}

		template <class U>
		auto operator != (const ComplexNumber<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] != b;
			return C;
		}

		template<class U>
		auto operator != (const Matrix<U> &b)
			->Matrix < decltype(T() + U()) >
		{
			if (isScalar())
				return b != mx[0][0];
			if (b.isScalar())
				return *this != b.mx[0][0];

			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] != b.mx[i][j];
			return C;
		}

		template <class U>
		auto operator != (const U &b)
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] != b;
			return C;
		}

		template<class U>
		auto operator < (const Matrix<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			if (isScalar())
				return b > mx[0][0];
			if (b.isScalar())
				return *this < b.mx[0][0];

			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] < b.mx[i][j];
			return C;
		}

		template <class U>
		auto operator < (const ComplexNumber<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] < b;
			return C;
		}

		template<class U>
		auto operator > (const Matrix<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			if (isScalar())
				return b < mx[0][0];
			if (b.isScalar())
				return *this > b.mx[0][0];

			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] > b.mx[i][j];
			return C;
		}

		template <class U>
		auto operator > (const ComplexNumber<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] > b;
			return C;
		}

		template<class U>
		auto operator <= (const Matrix<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			if (isScalar())
				return b >= mx[0][0];
			if (b.isScalar())
				return *this <= b.mx[0][0];

			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] == b.mx[i][j];
			return C;
		}

		template <class U>
		auto operator <= (const ComplexNumber<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] <= b;
			return C;
		}

		template<class U>
		auto operator >= (const Matrix<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			if (isScalar())
				return b <= mx[0][0];
			if (b.isScalar())
				return *this >= b.mx[0][0];

			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] >= b.mx[i][j];
			return C;
		}

		template <class U>
		auto operator >= (const ComplexNumber<U> &b) const
			->Matrix < decltype(T() + U()) >
		{
			Matrix<decltype(T() + U())> C(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[i][j] = mx[i][j] >= b;
			return C;
		}

		auto getVector() -> decltype(&mx) { return &mx; }

		int * getM_P(){ return &M; }
		int * getN_P(){ return &N; }

		virtual string toString() const override
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

		bool isScalar() const
		{
			return M == 1 && N == 1;
		}

		virtual bool operator == (const bool &b) const override
		{
			if (b)
				return checkIfTrue();
			else
				return checkIfFalse();

		}

		Matrix<T> transpose() const
		{
			Matrix<T> C(N, M);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					C.mx[j][i] = mx[i][j];
			return std::move(C);
		}

		operator int ()
		{
			return int(mx[0][0]);
		}

		template <class U>
		operator ComplexNumber<U>() const
		{
			if (M&&N)
				return ComplexNumber<U>(mx[0][0]);
			else
				throw "!";
		}

		private:
			bool checkIfTrue() const
			{
				if (M == 0 || N == 0)
					return false;
				for (int i = 0; i < M; i++)
					for (int j = 0; j < N; j++)
						if (mx[i][j] == 0)
							return false;
				return true;
			}

			bool checkIfFalse() const
			{
				if (M == 0 || N == 0)
					return true;
				for (int i = 0; i < M; i++)
					for (int j = 0; j < N; j++)
						if (mx[i][j] == 0)
							return true;
				return false;
			}
	};
};
