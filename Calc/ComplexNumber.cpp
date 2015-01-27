#include "stdafx.h"
#include "ComplexNumber.h"

namespace PR
{
	extern template class Numeric < ComplexNumber<double> >;
	extern template class Numeric < ComplexNumber<hdouble> >;

	template <class T> ComplexNumber<T>::ComplexNumber()
	{
		setDataType();
	}

	template <class T> ComplexNumber<T>::ComplexNumber(const double & reArg, const double & imArg = 0)
		:re(reArg), im(imArg)
	{
		setDataType();
	}

	template <class T> ComplexNumber<T>::ComplexNumber(const hdouble & reArg, const hdouble & imArg = 0)
		:re(reArg), im(imArg)
	{
		setDataType();
	}

	template <class T> ComplexNumber<T>::ComplexNumber(const ComplexNumber<T> &b)
		: re(b.re), im(b.im)
	{
		setDataType();
	}

	template <class T> ComplexNumber<T>::ComplexNumber(ComplexNumber<T> &&b)
		:re(b.re), im(b.im)
	{
		b.re = 0; b.im = 0;
		setDataType();
	}

	template <class T>
	ComplexNumber<T>& ComplexNumber<T>::operator=(const ComplexNumber<T> &b)
	{
		if (&b!=this)
		{ 
			re = b.re;
			im = b.im;
		}
		return *this;
	}

	template <class T>
	ComplexNumber<T>& ComplexNumber<T>::operator=(ComplexNumber<T> &&b)
	{
		if (&b != this)
		{
			re = b.re;
			im = b.im;
			b.re = 0;
			b.im = 0;
		}
		return *this;
	}

	template <> ComplexNumber<double>::ComplexNumber(string &&val)
	{
		if (val.size() && val.back() == 'i')
		{
			val.pop_back();
			im = atof(val.c_str());
			re = 0.0;
		}
		else
		{
			re = atof(val.c_str());
			im = 0.0;
		}
		_type = TYPE::DOUBLE;
	}

	template <> ComplexNumber<hdouble>::ComplexNumber(string &&val)
	{
		if (val.size() && val.back() == 'i')
		{
			val.pop_back();
			im.assign(std::move(val));
			re = 0.0;
		}
		else
		{
			re.assign(val);
			im = 0;
		}
		_type = TYPE::R_DOUBLE;
	}

	template <class T> ComplexNumber<T>::~ComplexNumber()
	{
	}

	template <> void ComplexNumber<double>::setDataType()
	{
		_type = TYPE::DOUBLE;
	}

	template <> void ComplexNumber<hdouble>::setDataType()
	{
		_type = TYPE::R_DOUBLE;
	}

	template <class T> T ComplexNumber<T>::getRe() const
	{
		return re;
	}

	template <class T> int ComplexNumber<T>::getReInt() const
	{
		return (int)re;
	}

	template <> int ComplexNumber<hdouble>::getReInt() const
	{
		return re.convert_to<int>();
	}

	template <class T> T ComplexNumber<T>::getIm() const
	{
		return im;
	}

	template <class T> void ComplexNumber<T>::setRe(const T &reA)
	{
		re = reA;
	}

	template <class T> void ComplexNumber<T>::setIm(const T &imA)
	{
		im = imA;
	}

	template <class T> 
	ComplexNumber<T> ComplexNumber<T>::operator + (const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re + b.re, im + b.im);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator - (const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re - b.re, im - b.im);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator * (const ComplexNumber<T> &b) const
	{
		ComplexNumber<T> c;
		c.re = re*b.re - im*b.im;
		c.im = re*b.im + im*b.re;
		return c;
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator / (const ComplexNumber<T> &b) const
	{
		ComplexNumber<T> c;
		if (im == 0 && b.im == 0)
		{
			c.re = re / b.re;
			c.im = 0;
		}
		else
		{
			auto denominator = b.re*b.re + b.im*b.im;
			c.re = (re*b.re + im*b.im) / denominator;
			c.im = (im*b.re - re*b.im) / denominator;
		}
		return c;
	}

	template <class T>
	void ComplexNumber<T>::operator/=(const ComplexNumber<T> &b)
	{
		if (im == 0 && b.im == 0)
		{
			re /= b.re;
		}
		else
		{
			auto denominator = b.re*b.re + b.im*b.im;
			re = (re*b.re + im*b.im) / denominator;
			im = (im*b.re - re*b.im) / denominator;
		}
	}

	template <class T>
	void ComplexNumber<T>::operator+=(const ComplexNumber<T> &b)
	{
		re += b.re;
		im += b.im;
	}

	template <class T>
	void ComplexNumber<T>::operator*=(const ComplexNumber<T> &b)
	{
		re = re*b.re - im*b.im;
		im = re*b.im + im*b.re;
	}

	template <class T>
	void ComplexNumber<T>::operator -= (const ComplexNumber<T> &b) 
	{
		re -= b.re;
		im -= b.im;
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::times(const ComplexNumber<T> &b) const
	{ 
		return *this * b;
	}

	template <class T> 
	ComplexNumber<T> ComplexNumber<T>::rdivide(const ComplexNumber<T> &b) const
	{
		return *this / b;
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::ldivide(const ComplexNumber<T> &b) const
	{
		return b / *this;
	}

	template <class T>
	ComplexNumber<T>& ComplexNumber<T>::operator = (const T &i)
	{
		re = i;
		im = 0;
		return *this;
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::neg() const
	{
		return ComplexNumber<T>(-re, -im);
	}
	
	template <class T>
	bool ComplexNumber<T>::operator == (const bool &b) const
	{
		return (re || im) == b;
	}

	template <class T> 
	ComplexNumber<T> ComplexNumber<T>::operator == (const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re == b.re && im == b.im);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator != (const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re != b.re || im != b.im);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator < (const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re < b.re);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator <= (const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re <= b.re);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator >(const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re > b.re);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator >= (const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re >= b.re);
	}


	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator | (const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re || b.re);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::operator & (const ComplexNumber<T> &b) const
	{
		return ComplexNumber<T>(re &&b.re);
	}


	template <class T>
	ComplexNumber<T> ComplexNumber<T>::logical_not() const
	{
		return ComplexNumber<T>(!re);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::transpose() const
	{
		return ComplexNumber<T>(*this);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::ctranspose() const
	{
		return conjugate();
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::conjugate() const
	{
		return ComplexNumber<T>(re, -im);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::rows() const
	{
		return ComplexNumber<T>(1);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::cols() const
	{
		return ComplexNumber<T>(1);
	}

	template <>
	string ComplexNumber<double>::toString() const
	{
		std::ostringstream ss;
		ss << re;
		if (im > 0)
			ss << "+";
		if (im != 0)
			ss << im << "i";
		return ss.str();
	}

	template <>
	string ComplexNumber<hdouble>::toString() const
	{
		std::ostringstream ss;
		ss << re;
		if (im > 0)
			ss << "+";
		if (im != 0)
			ss << im << "i";
		return ss.str();
	}

	template <>
	string ComplexNumber<hdouble>::toStringCommpact() const
	{
		std::ostringstream ss;
		if (re != 0 || im == 0)
			ss << re;
		if (im > 0 && re)
			ss << "+";
		if (im != 0)
			ss << im << "i";
		return ss.str();
	}

	template <>
	string ComplexNumber<double>::toStringCommpact() const
	{
		std::ostringstream ss;
		if (re!=0||im==0)
			ss << re;
		if (im > 0&&re)
			ss << "+";
		if (im != 0)
			ss << im << "i";
		return ss.str();
	}

	template<class T>
	string ComplexNumber<T>::toHtml() const
	{
		return "<table><tr><td>" + toString() + "</td></tr></table>";
	}

	template<>
	ComplexNumber<hdouble>::operator ComplexNumber<double>() const
	{
		return ComplexNumber<double>(re.convert_to<double>(), im.convert_to<double>());
	}

	template<>
	ComplexNumber<double>::operator ComplexNumber<hdouble>() const
	{
		return ComplexNumber<hdouble>(re, im);
	}

	template <class T>
	bool ComplexNumber<T>::checkForPositiveInteger() const
	{
		return im == 0 && re > 0 && re == floor(re);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::at(const ComplexNumber<T> &idx) const
	{
		if (!idx.checkForPositiveInteger())
			NumericException::throwIndexMustBeReal();
		if (idx.re > 1)
			NumericException::throwIndexOutOfRange();
		return *this;
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::at(const ComplexNumber<T> &f, const ComplexNumber<T> &s) const
	{
		if (!f.checkForPositiveInteger() || !s.checkForPositiveInteger())
			NumericException::throwIndexMustBeReal();
		if (f.re > 1 || s.re > 1)
			NumericException::throwIndexOutOfRange();
		return *this;
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::atColumn(int idx) const
	{
		if (idx < 0)
			NumericException::throwIndexMustBeReal();
		if (idx>1)
			NumericException::throwIndexOutOfRange();
		return *this;
	}

	template <class T>
	void ComplexNumber<T>::assign(const ComplexNumber<T> &data)
	{
		*this = data;
	}

	template <class T>
	void ComplexNumber<T>::assign(const ComplexNumber<T> &cell, const ComplexNumber<T> &data)
	{
		if (!cell.checkForPositiveInteger())
			NumericException::throwIndexMustBeReal();
		if (cell.re > 1)
			NumericException::throwIndexOutOfRange();
		*this = data;
	}

	template <class T>
	void ComplexNumber<T>::assign(const ComplexNumber<T> &row, const ComplexNumber<T> &col, const ComplexNumber<T> &data)
	{
		if (!row.checkForPositiveInteger() || !col.checkForPositiveInteger())
			NumericException::throwIndexMustBeReal();
		if (row.re > 1 || col.re > 1)
			NumericException::throwIndexOutOfRange();
		*this = data;
	}

	template<>
	void ComplexNumber<double>::computeIndex(int rows, int &i, int &j) const
	{
		j = ((int)re - 1) / rows;
		i = ((int)re - 1) % rows;
	}

	template<>
	void ComplexNumber<hdouble>::computeIndex(int rows, int &i, int &j) const
	{
		j = (re.convert_to<int>() - 1) / rows;
		i = (re.convert_to<int>() - 1) % rows;
	}

	template <class T>
	int ComplexNumber<T>::get_cols_int() const
	{ 
		return 1; 
	}

	template <class T>
	int ComplexNumber<T>::get_rows_int() const
	{ 
		return 1; 
	}

	template <class T>
	string ComplexNumber<T>::get_cell_string(int i, int j) const
	{
		if (i > 1 || j > 1)
			return "Out of range";
		return toString();
	}

	template <class T>
 	ComplexNumber<T> ComplexNumber<T>::getRowIndex() const
	{
		return ComplexNumber<T>(1);
	}
	
	template <class T>
	ComplexNumber<T> ComplexNumber<T>::getColIndex() const
	{
		return ComplexNumber<T>(1);
	}
	
	template <class T>
	ComplexNumber<T> ComplexNumber<T>::getIndexAll() const
	{
		return ComplexNumber<T>(1);
	}
	
	template <class T>
	ComplexNumber<T> ComplexNumber<T>::getIndex(int num) const
	{
		return ComplexNumber<T>(1);
	}

	template <class T>
	bool ComplexNumber<T>::isComplexNumber() const
	{
		return true;
	}

	template <class T>
	bool ComplexNumber<T>::isScalar() const
	{
		return true;
	}

	template <class T>
	bool ComplexNumber<T>::isInteger() const 
	{
		return im == 0.0 && floor(re) == re;
	}

	template <class T>
	bool ComplexNumber<T>::isReal() const 
	{
		return im == 0;
	}

	template <class T>
	shared_ptr<Data> ComplexNumber<T>::copy() const
	{
		return make_shared<ComplexNumber<T>>(*this);
	}

	template <class T> string ComplexNumber<T>::getValueInfoString() const
	{ 
		return toString(); 
	}

	template <class T> string ComplexNumber<T>::minValueString() const 
	{ 
		return toString(); 
	}

	template <class T> string ComplexNumber<T>::maxValueString() const 
	{ 
		return toString(); 
	}

	template <class T> vector<double> ComplexNumber<T>::toDoubleVector() const
	{
		return vector<double>(1, toDouble());
	}

	template <class T> vector<double> ComplexNumber<T>::toDoubleVectorAll() const
	{
		return vector<double>(1, toDouble());
	}

	template <class T> double ComplexNumber<T>::toDouble() const
	{
		return re;
	}

	template <class T> int ComplexNumber<T>::toInteger() const
	{
		return re;
	}

	template <> double ComplexNumber<hdouble>::toDouble() const
	{
		return re.convert_to<double>();
	}

	template <> int ComplexNumber<hdouble>::toInteger() const
	{
		return re.convert_to<int>();
	}


	template <class T> ComplexNumber<T> ComplexNumber<T>::getLastIndexOfRow() const{return ComplexNumber<T>(1);}
	template <class T> ComplexNumber<T> ComplexNumber<T>::getLastIndexOfCol() const{return ComplexNumber<T>(1);}

	template class ComplexNumber < double >;
	template class ComplexNumber < hdouble >;
}