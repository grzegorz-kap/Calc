#pragma once
#include "export.h"

#include <string>
#include <utility>
#include <complex>

using std::string;

#include "Numeric.h"

namespace PR
{
	class Power;

	template<class T> 
	class  ComplexNumber
		: public Numeric < ComplexNumber<T> >
	{
		template <class U>
		friend  class ComplexNumber;
		friend class Power;

		T re;
		T im;
	public:
		ComplexNumber()
		{
			_type = Data::TYPE_MAP[typeid(*this)];
		};

		ComplexNumber(T reArg, T imArg = 0.0) : re(reArg), im(imArg)
		{
			_type = Data::TYPE_MAP[typeid(*this)];
		};

		ComplexNumber(const string &val_str)
		{
			T *ref;
			string temp = val_str;
			re = 0;
			im = 0;
			if (temp.size() && temp.back() == 'i')
			{
				ref = &im;
				temp.pop_back();
			}
			else
				ref = &re;

			*ref = (T)atof(temp.c_str());
			_type = Data::TYPE_MAP[typeid(*this)];
		}

		~ComplexNumber(){};

		T getRe(){ return re; }
		T getIm(){ return im; }
		void setRe(T re){ this->re = re; }
		void setIm(T im){ this->im = im; }

		template <class U>
		ComplexNumber<T> operator + (const ComplexNumber<U> &b) const
		{
			return ComplexNumber<T>(re + b.re, im + b.im);
		}

		template <class U>
		ComplexNumber<T> operator - (const ComplexNumber<U> &b) const
		{
			return ComplexNumber<T>(re - b.re, im - b.im);
		}

		template <class U>
		ComplexNumber<T> operator * (const ComplexNumber<U> &b) const
		{
			ComplexNumber<T> c;
			c.re = re*b.re - im*b.im;
			c.im = re*b.im + im*b.re;
			return c;
		}

		template <class U>
		ComplexNumber<T> operator / (const ComplexNumber<U> &b) const
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

		/* Element wise multiplication */
		template <class U>
		auto times(const ComplexNumber<U> &b) const
			->ComplexNumber < decltype(T()*U()) >
		{
			return ComplexNumber<decltype(T() * U())>(*this * b);
		}

		template <class U>
		auto rdivide(const ComplexNumber<U> &b) const
			->ComplexNumber < decltype(T() / U()) >
		{
			return *this / b;
		}

		template <class U>
		auto ldivide(const ComplexNumber<U> &b) const
			->ComplexNumber < decltype(T() / U()) >
		{
			return b / *this;
		}

		template <class U>
		void operator += (const ComplexNumber<U> &b)
		{
			re += b.re; im += b.im;
		}

		template <class U>
		ComplexNumber<T> & operator = (U i)
		{
			re = i;
			return *this;
		}

		ComplexNumber<T> neg() const
		{
			return ComplexNumber<T>(-re, -im);
		}

		template <class U>
		ComplexNumber<T> operator == (const ComplexNumber<U> &b) const
		{
			return ComplexNumber<T>(re == b.re && im == b.im);
		}

		bool operator == (const bool &b) const
		{
			return (re || im) == b;
		}

		template <class U>
		ComplexNumber<T> operator != (const ComplexNumber<U> &b) const
		{
			return ComplexNumber<T>(re != b.re || im != b.im);
		}

		template <class U>
		ComplexNumber<T> operator < (const ComplexNumber<U> &b) const
		{
			return ComplexNumber<T>(re < b.re);
		}

		template <class U>
		ComplexNumber<T> operator <= (const ComplexNumber<U> &b) const
		{
			return ComplexNumber<T>(re <= b.re);
		}

		template <class U>
		ComplexNumber<T> operator >(const ComplexNumber<U> &b) const
		{
			return ComplexNumber<T>(re > b.re);
		}

		template <class U>
		ComplexNumber<T> operator >= (const ComplexNumber<U> &b) const
		{
			return ComplexNumber<T>(re >= b.re);
		}

		ComplexNumber<T> transpose() const
		{
			return ComplexNumber<T>(*this);
		}

		ComplexNumber<T> rows() const
		{
			return ComplexNumber<T>(1);
		}

		ComplexNumber<T> cols() const
		{
			return ComplexNumber<T>(1);
		}


		string toString() const
		{
			return std::to_string(re) + " " + std::to_string(im) + "i";
		}
	};
}