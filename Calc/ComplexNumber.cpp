#include "stdafx.h"
#include "ComplexNumber.h"

namespace PR
{
	template <class T>
	ComplexNumber<T>::ComplexNumber()
	{
		_type = Data::find_type(typeid(*this));
	}

	template <class T>
	ComplexNumber<T>::ComplexNumber(double reArg, double imArg = 0.0)
		:re(reArg), im(imArg)
	{
		_type = Data::find_type(typeid(*this));
	}

	template <class T>
	ComplexNumber<T>::ComplexNumber(hdouble reArg, hdouble imArg = 0)
		: re(reArg), im(imArg)
	{
		_type = Data::find_type(typeid(*this));
	};

	template <>
	ComplexNumber<double>::ComplexNumber(string &&val)
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

	template <>
	ComplexNumber<hdouble>::ComplexNumber(string &&val)
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

	template <class T>
	T ComplexNumber<T>::getRe() const
	{
		return re;
	}

	template <class T>
	T ComplexNumber<T>::getIm() const
	{
		return im;
	}

	template <class T>
	void ComplexNumber<T>::setRe(const T &reA)
	{
		re = reA;
	}

	template <class T>
	void ComplexNumber<T>::setIm(const T &imA)
	{
		im = imA;
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::operator + (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() + U())>
	{
		return ComplexNumber<decltype(T() + U())>(re + b.re, im + b.im);
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::operator - (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() - U())>
	{
		return ComplexNumber<decltype(T() - U())>(re - b.re, im - b.im);
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::operator * (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() * U())>
	{
		ComplexNumber<decltype(T() * U())> c;
		c.re = re*b.re - im*b.im;
		c.im = re*b.im + im*b.re;
		return c;
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::operator / (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() / U())>
	{
		ComplexNumber<decltype(T() / U())> c;
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

	template <class T> template <class U>
	auto ComplexNumber<T>::times(const ComplexNumber<U> &b) const
		->ComplexNumber < decltype(T()*U()) >
	{
		return *this * b;
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::rdivide(const ComplexNumber<U> &b) const
		->ComplexNumber < decltype(T()*U()) >
	{
		return *this / b;
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::ldivide(const ComplexNumber<U> &b) const
		->ComplexNumber < decltype(T()*U()) >
	{
		return b / *this;
	}

	template <class T>
	ComplexNumber<T>& ComplexNumber<T>::operator = (const T &i)
	{
		re = i;
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

	template <class T> template <class U>
	auto ComplexNumber<T>::operator == (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() + U())>
	{
		return ComplexNumber<decltype(T() + U())>(re == b.re && im == b.im);
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::operator != (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() + U())>
	{
		return ComplexNumber<decltype(T() + U())>(re != b.re || im != b.im);
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::operator < (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() + U())>
	{
		return ComplexNumber<decltype(T() + U())>(re < b.re);
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::operator <= (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() + U())>
	{
		return ComplexNumber<decltype(T() + U())>(re <= b.re);
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::operator > (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() + U())>
	{
		return ComplexNumber<decltype(T() + U())>(re > b.re);
	}

	template <class T> template <class U>
	auto ComplexNumber<T>::operator >= (const ComplexNumber<U> &b) const
		->ComplexNumber<decltype(T() + U())>
	{
		return ComplexNumber<decltype(T() + U())>(re >= b.re);
	}

	template <class T>
	ComplexNumber<T> ComplexNumber<T>::transpose() const
	{
		return ComplexNumber<T>(*this);
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
		return ((ComplexNumber<double>)*this).toString();
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

	template class ComplexNumber < double > ;
	template class ComplexNumber < hdouble > ;
}