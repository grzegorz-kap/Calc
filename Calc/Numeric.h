#pragma once

#include <memory>

using std::unique_ptr;
using std::make_unique;

#include  "Data.h"

namespace PR
{
	template <class A>
	class Matrix;

	template <class T>
	class Numeric
		:public Data
	{
	public:

		Numeric()
		{
		}

		~Numeric()
		{
		}

		template <class U>
		unique_ptr<T>  operator + (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() + *(b->get_derived()));
		}

		virtual unique_ptr<Data> operator + (unique_ptr<Data> &b) const override
		{
			if (_type==b->_type)
				return *this + b->cast_numeric<T>();
			else
				return *this + (b->convert_numeric<T>()).get();
		}

		template <class U>
		unique_ptr<T>  operator - (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() - *(b->get_derived()));
		}

		virtual unique_ptr<Data> operator - (unique_ptr<Data> &b) const override
		{
			if (_type == b->_type)
				return *this - b->cast_numeric<T>();
			else
				return *this - (b->convert_numeric<T>()).get();
		}

		template <class U>
		unique_ptr<T>  operator * (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() * *(b->get_derived()));
		}

		virtual unique_ptr<Data> operator * (unique_ptr<Data> &b) const override
		{
			if (_type == b->_type)
				return *this * b->cast_numeric<T>();
			else
				return *this * (b->convert_numeric<T>()).get();
		}

		template <class U>
		unique_ptr<T>  operator / (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() / *(b->get_derived()));
		}

		virtual unique_ptr<Data> operator / (unique_ptr<Data> &b) const override
		{
			if (_type == b->_type)
				return *this / b->cast_numeric<T>();
			else
				return *this / (b->convert_numeric<T>()).get();
		}
		
	private:

	

		const T * get_derived() const
		{
			return dynamic_cast<const T *>(this);
		}

		template <class U>
		friend class Numeric;
	};

}
