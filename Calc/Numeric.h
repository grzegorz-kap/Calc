#pragma once

#include <memory>

using std::shared_ptr;
using std::make_unique;

#include  "Data.h"
#include "Mathematic.h"

namespace PR
{
	template <class A>
	class Matrix;

	template <class A>
	class ComplexNumber;

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

		virtual bool isNumeric() const override
		{
			return true;
		}

		virtual shared_ptr<Data> operator + (shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() + *(b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> operator - (shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() - *(b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> operator * (shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() * *(b->cast_numeric<T>()->get_derived()));
		}


		virtual shared_ptr<Data> operator / (shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() / *(b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> exponentiation(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(Mathematic::power(*get_derived(), *b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> mexponentiation(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(Mathematic::mpower(*get_derived(), *b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> log() const override
		{
			return make_shared<T>(Mathematic::logarithm(*get_derived()));
		}

		virtual shared_ptr<Data> log2() const override
		{
			return make_shared<T>(Mathematic::logarithm2(*get_derived()));
		}

		virtual shared_ptr<Data> log10() const override
		{
			return make_shared<T>(Mathematic::logarithm10(*get_derived()));
		}

		virtual shared_ptr<Data> log(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(Mathematic::logarithm(*get_derived(), *b->cast_numeric<T>()->get_derived()));
		}

		virtual shared_ptr<Data> sin() const override
		{
			return make_shared<T>(Mathematic::sinus(*get_derived()));
		}

		virtual shared_ptr<Data> cos() const override
		{
			return make_shared<T>(Mathematic::cosinus(*get_derived()));
		}

		virtual shared_ptr<Data> tan() const
		{
			return make_shared<T>(Mathematic::tangens(*get_derived()));
		}

		virtual shared_ptr<Data> lu() const
		{
			return make_shared<T>(Mathematic::lu(*get_derived()));
		}

		virtual shared_ptr<Data> operator -() const override
		{
			return make_shared<T>(get_derived()->neg());
		}

		virtual shared_ptr<Data> times(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(get_derived()->times(*(b->cast_numeric<T>()->get_derived())));
		}

		virtual shared_ptr<Data> rdivide(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(get_derived()->rdivide(*(b->cast_numeric<T>()->get_derived())));
		}

		virtual shared_ptr<Data> eq(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() == *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> ge(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() >= *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> gt(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() > *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> le(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() <= *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> lt(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() < *b->cast_numeric<T>()->get_derived());
		}

		virtual shared_ptr<Data> ne(shared_ptr<Data> &b) const override
		{
			return make_shared<T>(*get_derived() != *b->cast_numeric<T>()->get_derived());
		}

		virtual bool operator == (const bool &b) const override
		{
			return false;
		}

		virtual shared_ptr<Data> get_rows() const override
		{
			return make_shared<T>(get_derived()->rows());
		}

		virtual shared_ptr<Data> get_cols() const override
		{
			return make_shared<T>(get_derived()->cols());
		}

		virtual shared_ptr<Data> transposition() const override
		{
			return make_shared<T>(get_derived()->transpose());
		}

		
	private:
		const T * get_derived() const
		{
			return dynamic_cast<const T *>(this);
		}

		template <class U>
		friend class Numeric;
	};

};
