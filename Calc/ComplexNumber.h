#pragma once
#include <string>
#include <utility>
#include <sstream>

using std::string;

#include "Numeric.h"
#include "NumericException.h"

namespace PR
{
	//class Mathematic;
	//template <class X> class Matrix;

	template<class T> class  ComplexNumber : public Numeric < ComplexNumber<T> >
	{
		/*template <class U> friend  class ComplexNumber;
		template <class X> friend class Matrix;
		friend class Mathematic;
		*/
		void setDataType();
	public:
		T re;
		T im;
		
		ComplexNumber();
		ComplexNumber(const double & reArg, const double & imArg = 0);
		ComplexNumber(const hdouble & reArg, const hdouble & imArg = 0);
		ComplexNumber(string &&val_str);
		~ComplexNumber();
		void operator += (const ComplexNumber<T> &b);
		ComplexNumber<T> & operator = (const T &i);
		T getRe() const;
		T getIm() const;
		void setRe(const T &re);
		void setIm(const T &im);
		int getReInt() const;
		ComplexNumber<T> operator + (const ComplexNumber<T> &b) const ;	
		ComplexNumber<T> operator - (const ComplexNumber<T> &b) const ;
		ComplexNumber<T> operator * (const ComplexNumber<T> &b) const ;
		ComplexNumber<T> operator / (const ComplexNumber<T> &b) const ;
		void operator /= (const ComplexNumber<T> &b);
		void operator -= (const ComplexNumber<T> &b);
		void operator *= (const ComplexNumber<T> &b);
		ComplexNumber<T> times  (const ComplexNumber<T> &b) const; 
		ComplexNumber<T> rdivide(const ComplexNumber<T> &b) const; 
		ComplexNumber<T> ldivide(const ComplexNumber<T> &b) const; 
		ComplexNumber<T> neg() const;
		ComplexNumber<T> conjugate() const;
		ComplexNumber<T> operator == (const ComplexNumber<T> &b) const;
		ComplexNumber<T> operator != (const ComplexNumber<T> &b) const;
		ComplexNumber<T> operator <  (const ComplexNumber<T> &b) const;
		ComplexNumber<T> operator <= (const ComplexNumber<T> &b) const;
		ComplexNumber<T> operator >  (const ComplexNumber<T> &b) const;
		ComplexNumber<T> operator >= (const ComplexNumber<T> &b) const;
		ComplexNumber<T> operator | (const ComplexNumber<T> &b) const;
		ComplexNumber<T> operator & (const ComplexNumber<T> &b) const;
		ComplexNumber<T> logical_not() const;
		bool operator == (const bool &b) const;
		virtual int get_cols_int() const override;
		virtual int get_rows_int() const override;
		virtual string get_cell_string(int i, int j) const override;
		ComplexNumber<T> transpose() const;
		ComplexNumber<T> ctranspose() const;
		ComplexNumber<T> rows() const;
		ComplexNumber<T> cols() const;
		ComplexNumber<T> at(const ComplexNumber<T> &cell) const;
		ComplexNumber<T> at(const ComplexNumber<T> &first, const ComplexNumber<T> &second) const;
		ComplexNumber<T> atColumn(int idx) const;
		void assign(const ComplexNumber<T> &data);
		void assign(const ComplexNumber<T> &cell, const ComplexNumber<T> &data);
		void assign(const ComplexNumber<T> &row, const ComplexNumber<T> &col, const ComplexNumber<T> &data);
		ComplexNumber<T> getRowIndex() const;
		ComplexNumber<T> getColIndex() const;
		ComplexNumber<T> getIndexAll() const;
		ComplexNumber<T> getIndex(int num) const;
		bool checkForPositiveInteger() const;
		void computeIndex(int rows, int &i, int &j) const;
		string toString() const;
		virtual string toStringCommpact() const override;
		string toHtml() const;
		operator ComplexNumber<hdouble>() const;
		operator ComplexNumber<double>() const;
		virtual bool isComplexNumber() const override;
		virtual bool isScalar() const override;
		virtual bool isInteger() const override;
		virtual bool isReal() const override;
		virtual shared_ptr<Data> copy() const	override;
		virtual string getValueInfoString() const;
		virtual string minValueString() const ;
		virtual string maxValueString() const ;
		virtual vector<double> toDoubleVector() const override;
		virtual vector<double> toDoubleVectorAll() const override;
		double toDouble() const;
		int toInteger() const;
		ComplexNumber<T> getLastIndexOfRow() const;
		ComplexNumber<T> getLastIndexOfCol() const;
	};

}