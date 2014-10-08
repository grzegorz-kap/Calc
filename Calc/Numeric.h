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
		unique_ptr<T>  operator + (const unique_ptr<Numeric<U>> &b) const
		{
			return make_unique<T>(*get_derived() + *(b->get_derived()));
		}

		virtual unique_ptr<Data> operator + (const unique_ptr<Data> &b) const override
		{
			return *this + b->cast_numeric<T>();
		}

		template <class U>
		unique_ptr<T>  operator - (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() - *(b->get_derived()));
		}

		virtual unique_ptr<Data> operator - (const unique_ptr<Data> &b) const override
		{
			return *this - (b->cast_numeric<T>());
		}

		template <class U>
		unique_ptr<T>  operator * (const Numeric<U> *b) const
		{
			const U * p = static_cast<const U *>(b);
			return make_unique<T>(*get_derived() * *(b->get_derived()));
		}

		virtual unique_ptr<Data> operator * (const unique_ptr<Data> &b) const override
		{
			return *this * (b->cast_numeric<T>()).get();
		}

		template <class U>
		unique_ptr<T>  operator / (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() / *(b->get_derived()));
		}

		virtual unique_ptr<Data> operator / (const unique_ptr<Data> &b) const override
		{
			return *this / (b->cast_numeric<T>());
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
