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
	//template <class T> class ComplexNumber;
	class Mathematic;
	class MatrixUtils;
	template <class T> class MatrixBuilder;

	//! Klasa reprezentujaca macierz.
	template<class T> 
	class  Matrix : public Numeric<Matrix<T>>
	{

		friend class MatrixTransposer;
		friend class Mathematic;
		friend class MatrixUtils;
		template<class T> friend class MatrixBuilder;
		template<class U> friend class Matrix;
		
		static Matrix<T>(*matrix_divide)(const Matrix<T> &a, const Matrix<T> &b);

	protected:
		vector< vector< ComplexNumber<T> >> mx;
		int M;
		int N;		
	public:
		
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
		void rows(int arg);
		void cols(int arg);
		int rows() const;
		int cols() const;
		virtual int get_cols_int() const override;
		virtual int get_rows_int() const override;
		virtual string get_cell_string(int i, int j) const override;
		ComplexNumber<T>& operator()(int i, int j);
		Matrix<T> rdivide(const Matrix<T> &b) const;
		Matrix<T> rdivide(const ComplexNumber<T> &b) const;
		Matrix<T> ldivide(const ComplexNumber<T> &b) const;
		Matrix<T> times(const Matrix<T> &b) const;
		Matrix<T> operator + (const Matrix<T> &B) const;
		Matrix<T> operator + (const ComplexNumber<T> &b) const;
		Matrix<T> operator - (const Matrix<T> &B) const;
		Matrix<T> sub(const ComplexNumber<T> &b) const;
		Matrix<T> operator - (const ComplexNumber<T> &b) const;
		Matrix<T> operator * (const Matrix<T> &B) const;
		Matrix<T> operator * (const ComplexNumber<T> &b) const;
		Matrix<T> operator / (const ComplexNumber<T> &b) const;
		Matrix<T> operator == (const Matrix<T> &b) const;
		Matrix<T> operator == (const ComplexNumber<T> &b) const;
		Matrix<T> operator != (const Matrix<T> &b) const;
		Matrix<T> operator != (const ComplexNumber<T> &b) const;
		Matrix<T> operator != (const T &b) const;
		Matrix<T> operator < (const Matrix<T> &b) const;
		Matrix<T> operator < (const ComplexNumber<T> &b) const;
		Matrix<T> operator > (const Matrix<T> &b) const;
		Matrix<T> operator > (const ComplexNumber<T> &b) const;
		Matrix<T> operator <= (const Matrix<T> &b) const;
		Matrix<T> operator <= (const ComplexNumber<T> &b) const;
		Matrix<T> operator >= (const Matrix<T> &b) const;
		Matrix<T> operator >= (const ComplexNumber<T> &b) const;
		Matrix<T> operator / (const Matrix<T> &B) const;
		Matrix<T> transpose() const;
		Matrix<T> ctranspose() const;
		Matrix<T> neg() const;
		Matrix<T> conjugate() const;
		Matrix<T> operator | (const Matrix<T> &b) const;
		Matrix<T> operator & (const Matrix<T> &b) const;
		Matrix<T> logical_not() const;
		vector<vector<ComplexNumber<T>>>* Matrix<T>::getVector();
		int * getM_P();	
		int * getN_P();
		bool virtual isScalar() const override;
		bool virtual isInteger() const override;
		bool virtual isReal() const override;
		int virtual toInteger() const override;
		Matrix<T> at(const Matrix<T> &cells) const;
		Matrix<T> at(const Matrix<T> &first, const Matrix<T> &second) const;
		Matrix<T> atColumn(int idx) const;
		void assign(const Matrix<T> &b);
		void deleteAt(const Matrix<T> &row, const Matrix<T> &col);
		void assign(const Matrix<T> &cells, const Matrix<T> &data);
		void assign(const Matrix<T> &cells, const ComplexNumber<T> &data);
		void assign(const Matrix<T> &row, const Matrix<T> &col, const Matrix<T> &data);
		void assign(const Matrix<T> &row, const Matrix<T> &col, const ComplexNumber<T> &data);
		void checkForPositiveInteger() const;
		Matrix<T> getIndex(int num) const;
		Matrix<T> getIndexAll() const;
		Matrix<T> getRowIndex() const;
		Matrix<T> getColIndex() const;
		virtual int getRowsCountForEmptyMatrixAssignment() const override;
		virtual int getColsCountForEmptyMatrixAssignment() const override;
		void expandRowsTo(int idx, const ComplexNumber<T> &value);
		void expandColsTo(int idx, const ComplexNumber<T> &value);
		virtual string toHtml() const override;
		virtual string toString() const override;
		virtual string toStringCommpact() const override;
		virtual bool operator == (const bool &b) const override;
		virtual bool isEmpty() const override;
		virtual bool isMatrix() const override;
		virtual string getValueInfoString() const override;
		ComplexNumber<T> minValue() const;
		ComplexNumber<T> maxValue() const;
		virtual string minValueString() const override;
		virtual string maxValueString() const override;
		virtual shared_ptr<Data> copy() const;
		virtual vector<double> toDoubleVector() const override;
		virtual vector<double> toDoubleVectorAll() const override;

		operator ComplexNumber<double>() const;
		operator ComplexNumber<hdouble>() const;
		operator Matrix<double>() const;
		operator Matrix<hdouble>()const;

		Matrix<T> getLastIndexOfCol() const;
		Matrix<T> getLastIndexOfRow() const;

		private:
			bool checkIfTrue() const;
			bool checkIfFalse() const;
	};


};
