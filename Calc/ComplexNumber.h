#pragma once

#include <string>
#include <utility>

using std::string;
using std::forward;

#include "export.h"

namespace PR
{

	template<class T> class  ComplexNumber
	{
		template <class U>
		friend  class ComplexNumber;

		T re;
		T im;
	public:
		ComplexNumber(){};

		ComplexNumber(T reArg, T imArg = 0.0) : re(reArg), im(imArg)
		{
		};

		template <typename T, typename U>
		ComplexNumber<U> cast(const ComplexNumber<T> &b)
		{
			return ComplexNumber<U> a(b.re, b.im);
		}

		/*ComplexNumber(ComplexNumber<T> &&other)
			:re(0), im(0)
		{
			*this = std::move(other);
		}

		ComplexNumber<T> & operator = (ComplexNumber<T> &&o)
		{
			if (this != &o)
			{
				re = o.re;
				im = o.im;

				o.re = 0;
				o.im = 0;
			}
			return *this;
		}*/

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
		}

		~ComplexNumber(){};

		T getRe(){ return re; }
		T getIm(){ return im; }
		void setRe(T re){ this->re = re; }
		void setIm(T im){ this->im = im; }

		ComplexNumber<T> operator - () const
		{
			return ComplexNumber<T>(-re, -im);
		}

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

		template <class U>
		void operator += (const ComplexNumber<U> &b)
		{ 
			re += b.re; im += b.im; 
		}

		template <class U>
		bool operator == (const ComplexNumber<U> &b) const
		{
			if (re != b.re || im != b.im)
				return false;
			else
				return true;
		}

		template <class U>
		ComplexNumber<T> & operator = (U i)
		{
			re = i;
			return *this;
		}

		string toString() const
		{
			return std::to_string(re) + " " + std::to_string(im) + "i";
		}
	};
}
