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

		void setDataType();

		void rows(int arg){ M = arg; }
		void cols(int arg){ N = arg; }
		int rows() const;
		int cols() const;
		virtual int get_cols_int() const override { return N; }
		virtual int get_rows_int() const override { return M; }
		virtual string get_cell_string(int i, int j) const override;
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


		Matrix<T> operator | (const Matrix<T> &b) const
		{
			if (M != b.M || N != b.N)
				throw NumericException("Error using | . Matrix sizes must agree");
			Matrix<T> c(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					c.mx[i][j] = mx[i][j] | b.mx[i][j];
			return c;
		}

		Matrix<T> operator & (const Matrix<T> &b) const
		{
			if (M != b.M || N != b.N)
				throw NumericException("Error using & . Matrix sizes must agree");
			Matrix<T> c(M, N);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
					c.mx[i][j] = mx[i][j] & b.mx[i][j];
			return c;
		}

		vector<vector<ComplexNumber<T>>>* Matrix<T>::getVector();

		int * getM_P()
		{ 
			return &M; 
		}
		
		int * getN_P()
		{ 
			return &N; 
		}
		
		bool virtual isScalar() const override
		{
			return M == 1 && N == 1;
		}

		bool virtual isInteger() const override
		{
			return isScalar() && mx[0][0].isInteger();
		}

		bool virtual isReal() const override
		{
			for (const auto &row : mx)
				for (const auto &element : row)
					if (!element.isReal())
						return false;
			return true;
		}

		int virtual toInteger() const override
		{
			return mx[0][0].toInteger();
		}

		Matrix<T> at(const Matrix<T> &cells) const;
		Matrix<T> at(const Matrix<T> &first, const Matrix<T> &second) const;
		Matrix<T> atColumn(int idx) const;

		void assign(const Matrix<T> &b);
		void assign(const Matrix<T> &cells, const Matrix<T> &data);
		void assign(const Matrix<T> &cells, const ComplexNumber<T> &data);
		void assign(const Matrix<T> &row, const Matrix<T> &col, const Matrix<T> &data);
		void assign(const Matrix<T> &row, const Matrix<T> &col, const ComplexNumber<T> &data);
		void checkForPositiveInteger() const;

		Matrix<T> getIndex(int num) const;
		Matrix<T> getIndexAll() const;
		Matrix<T> getRowIndex() const { return getIndex(M); }
		Matrix<T> getColIndex() const { return getIndex(N); }

		virtual int getRowsCountForEmptyMatrixAssignment() const override;
		virtual int getColsCountForEmptyMatrixAssignment() const override;

		void expandRowsTo(int idx, const ComplexNumber<T> &value);
		void expandColsTo(int idx, const ComplexNumber<T> &value);

		virtual string toHtml() const override;
		virtual string toString() const override;
		virtual bool operator == (const bool &b) const override;
		virtual bool isEmpty() const override { return M == 0 && N == 0; }

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

		virtual bool isMatrix() const override{ return true; }
		virtual string getValueInfoString() const override;

		ComplexNumber<T> minValue() const;
		ComplexNumber<T> maxValue() const;
		virtual string minValueString() const override;
		virtual string maxValueString() const override;

		virtual Data* copy() const
		{
			return new Matrix<T>(*this);
		}


		virtual vector<double> toDoubleVector() const override
		{
			if (!M)
				return vector<double>();
			vector<double> out;
			out.reserve(N);
			for (const ComplexNumber<T> &element : mx[0])
			{
				out.push_back(element.toDouble());
			}
			return out;
		}

		virtual vector<double> toDoubleVectorAll() const override
		{
			vector<double> out;
			out.reserve(M*N);
			for (const auto &row : mx)
			{
				for (const auto &cell : row)
				{
					out.push_back(cell.toDouble());
				}
			}
			return out;
		}

		private:
			bool checkIfTrue() const;
			bool checkIfFalse() const;
	};


};
