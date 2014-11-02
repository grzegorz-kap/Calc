#pragma once

#include <vector>
#include <memory>

#include "ComplexNumber.h"
#include "functions.h"
#include "NumericException.h"

using std::vector;
using std::shared_ptr;

namespace PR
{
	template <class T>
	class ComplexNumber;
	class Mathematic;
	class MatrixUtils;
	template <class T>
	class MatrixBuilder;

	template<class T> class  Matrix
		: public Numeric<Matrix<T>>
	{
		
		static Matrix<T>(*matrix_divide)(const Matrix<T> &a, const Matrix<T> &b);

	protected:
		vector< vector< ComplexNumber<T> >> mx;
		int M;
		int N;

		
	public:
		friend class MatrixTransposer;
		friend class Mathematic;
		friend class MatrixUtils;
		template<class T> friend class MatrixBuilder;
		template<class U> friend class Matrix;
		Matrix();
		Matrix(const ComplexNumber<T> &b);
		Matrix(Matrix<T> &&other);
		Matrix(const Matrix<T> &b);
		Matrix(string &&scalar);
		Matrix(int m, int n);
		Matrix(int m, int n, const ComplexNumber<T> &value);
		template <class U>Matrix(const vector< vector< ComplexNumber<U> >> &);
		virtual ~Matrix();

		Matrix<T> & operator = (const Matrix<T> &b);
		Matrix<T> & operator = (Matrix<T> &&other);

		void rows(int arg){ M = arg; }
		void cols(int arg){ N = arg; }
		int rows() const;
		int cols() const;
		ComplexNumber<T>& operator()(int i, int j);

		template <class U> auto rdivide(const Matrix<U> &b) const->Matrix < decltype(T() + U()) > ;
		template <class U> auto rdivide(const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto ldivide(const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto times(const Matrix<U> &b) const->Matrix < decltype(T() + U()) > ;
		Matrix<T> transpose() const;
		Matrix<T> neg() const;

		template <class U> auto operator + (const Matrix<U> &B) const->Matrix < decltype(T() + U()) > ;
		template <class U> auto operator + (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator - (const Matrix<U> &B) const->Matrix < decltype(T() + U()) >;
		template <class U> auto sub(const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator - (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator * (const Matrix<U> &B) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator * (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		Matrix<T> operator / (const Matrix<T> &B) const;
		template <class U> auto operator / (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		
		template <class U> auto operator == (const Matrix<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator == (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator != (const Matrix<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator != (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator != (const U &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator < (const Matrix<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator < (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator > (const Matrix<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator > (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator <= (const Matrix<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator <= (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator >= (const Matrix<U> &b) const->Matrix < decltype(T() + U()) >;
		template <class U> auto operator >= (const ComplexNumber<U> &b) const->Matrix < decltype(T() + U()) >;

		vector<vector<ComplexNumber<T>>>* Matrix<T>::getVector();

		int * getM_P(){ return &M; }
		int * getN_P(){ return &N; }
		bool isScalar() const
		{
			return M == 1 && N == 1;
		}

		Matrix<T> at(const Matrix<T> &cells) const;
		Matrix<T> at(const Matrix<T> &first, const Matrix<T> &second) const;

		virtual string toHtml() const override;
		virtual string toString() const override;
		virtual bool operator == (const bool &b) const override;

		template <class U>
		operator ComplexNumber<U>() const
		{
			if (M&&N)
				return ComplexNumber<U>(mx[0][0]);
			else
				throw "!";
		}

		operator Matrix<double>() const;
		operator Matrix<hdouble>()const;
		
	

		private:
			bool checkIfTrue() const;
			bool checkIfFalse() const;
	};
};
