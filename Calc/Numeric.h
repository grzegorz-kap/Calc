#pragma once

#include <memory>

using std::shared_ptr;
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
		shared_ptr<T>  operator + (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() + *(b->get_derived()));
		}

		virtual shared_ptr<Data> operator + (shared_ptr<Data> &b) const override
		{
			return *this + b->cast_numeric<T>();
		}

		template <class U>
		shared_ptr<T>  operator - (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() - *(b->get_derived()));
		}

		virtual shared_ptr<Data> operator - (shared_ptr<Data> &b) const override
		{
			return *this - b->cast_numeric<T>();
		}

		template <class U>
		shared_ptr<T>  operator * (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() * *(b->get_derived()));
		}

		virtual shared_ptr<Data> operator * (shared_ptr<Data> &b) const override
		{
			return *this * b->cast_numeric<T>();
		}

		template <class U>
		shared_ptr<T>  operator / (const Numeric<U> *b) const
		{
			return make_unique<T>(*get_derived() / *(b->get_derived()));
		}

		virtual shared_ptr<Data> operator / (shared_ptr<Data> &b) const override
		{
			return *this / b->cast_numeric<T>();
		}

		template <class U>
		shared_ptr<T> exponentiation(const Numeric<U> *b) const
		{
			return shared_ptr<T>();
		}

		virtual shared_ptr<Data> exponentiation(shared_ptr<Data> &b) const override
		{
			return this->exponentiation(b->cast_numeric<T>());
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
