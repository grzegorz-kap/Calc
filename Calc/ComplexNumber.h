#pragma once
#include "export.h"

#include <string>
#include <utility>
#include <complex>
#include <sstream>

using std::string;

#include "Numeric.h"
#include "NumericException.h"

namespace PR
{
	class Mathematic;

	template <class X> class Matrix;

	template<class T> 
	class  ComplexNumber
		: public Numeric < ComplexNumber<T> >
	{
		template <class U> friend  class ComplexNumber;
		template <class X> friend class Matrix;
		friend class Mathematic;

		T re;
		T im;
	public:
		
		ComplexNumber();
		ComplexNumber(double reArg, double imArg = 0);
		ComplexNumber(hdouble reArg, hdouble imArg = 0);
		ComplexNumber(string &&val_str);
		~ComplexNumber(){};

		void operator += (const ComplexNumber<T> &b);
		ComplexNumber<T> & operator = (const T &i);

		T getRe() const;
		T getIm() const;
		void setRe(const T &re);
		void setIm(const T &im);

		int getReInt() const;

		template <class U> auto operator + (const ComplexNumber<U> &b) const ->ComplexNumber < decltype(T() + U()) > ;	
		template <class U> auto operator - (const ComplexNumber<U> &b) const ->ComplexNumber < decltype(T() - U()) > ;
		template <class U> auto operator * (const ComplexNumber<U> &b) const ->ComplexNumber < decltype(T() * U()) > ;
		template <class U> auto operator / (const ComplexNumber<U> &b) const ->ComplexNumber < decltype(T() / U()) > ;
		
		void operator /= (const ComplexNumber<T> &b);
		void operator -= (const ComplexNumber<T> &b);
		void operator *= (const ComplexNumber<T> &b);
		
		template <class U> auto times(const ComplexNumber<U> &b) const -> ComplexNumber < decltype(T()*U()) > ; /* Element wise multiplication */
		template <class U> auto rdivide(const ComplexNumber<U> &b) const->ComplexNumber < decltype(T() / U()) >; /*  *this/b  */
		template <class U> auto ldivide(const ComplexNumber<U> &b) const->ComplexNumber < decltype(T() / U()) > ; /*  b/*this  */
		
		ComplexNumber<T> neg() const;

		template <class U> auto operator == (const ComplexNumber<U> &b) const->ComplexNumber < decltype(T() + U()) > ;
		template <class U> auto operator != (const ComplexNumber<U> &b) const->ComplexNumber < decltype(T() + U()) >;
		template <class U> auto operator < (const ComplexNumber<U> &b) const->ComplexNumber < decltype(T() + U()) >;
		template <class U> auto operator <= (const ComplexNumber<U> &b) const->ComplexNumber < decltype(T() + U()) >;
		template <class U> auto operator > (const ComplexNumber<U> &b) const->ComplexNumber < decltype(T() + U()) >;
		template <class U> auto operator >= (const ComplexNumber<U> &b) const->ComplexNumber < decltype(T() + U()) >;
		bool operator == (const bool &b) const;

		ComplexNumber<T> transpose() const;
		ComplexNumber<T> rows() const;
		ComplexNumber<T> cols() const;

		ComplexNumber<T> at(const ComplexNumber<T> &cell) const;
		ComplexNumber<T> at(const ComplexNumber<T> &first, const ComplexNumber<T> &second) const;

		void assign(const ComplexNumber<T> &data);
		void assign(const ComplexNumber<T> &cell, const ComplexNumber<T> &data);
		void assign(const ComplexNumber<T> &row, const ComplexNumber<T> &col, const ComplexNumber<T> &data);

		bool checkForPositiveInteger() const;
		void computeIndex(int rows, int &i, int &j) const;

		string toString() const;
		string toHtml() const;

		operator ComplexNumber<hdouble>() const;
		operator ComplexNumber<double>() const;

	};
}