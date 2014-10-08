#pragma once

#include "Numeric.h"

namespace PR
{
	template<class Z>
	class Matrix;

	/*
	Class wrapper for standard C++ numeric types
	*/
	template <class T>
	class Value
		: public Numeric<Value<T>>
	{
	private:

		T value;

	public:

		Value()
		{
			_type = Data::TYPE_MAP[typeid(*this)];
		}

		Value(const Value<T> &b)
		{
			_type = Data::TYPE_MAP[typeid(*this)];
			value=b.value;
		}

		Value(const T &b)
			:value(b)
		{
			_type = Data::TYPE_MAP[typeid(*this)];
		}

		virtual ~Value()
		{
		}

		template <class U>
		auto operator + (const Value<U> &b) const
			-> Value< decltype(T()+U()) >
		{
			return Value<decltype(T()+U())>(value + b.value);
		}

		template <class U>
		auto operator - (const Value<U> &b) const
			-> Value< decltype(T() - U()) >
		{
			return Value<decltype(T() - U())>(value - b.value);
		}

		template <class U>
		auto operator * (const Value<U> &b) const
			-> Value< decltype(T() * U()) >
		{
			return Value<decltype(T() * U())>(value * b.value);
		}

		template <class U>
		auto operator / (const Value<U> &b) const
			-> Value< decltype(T() / U()) >
		{
			return Value<decltype(T() / U())>(value / b.value);
		}

		template <class X>
		operator Value<X>()
		{
			return Value<X>(value);
		}

		template <class X>
		operator Matrix<X>()
		{
			return Matrix<X>(value);
		}

		template <class X>
		operator X()
		{
			return X(value);
		}
		
		template <class U>
		friend class Value;
	};
}

