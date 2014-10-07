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
		}

		Value(const Value<T> &b)
		{
			value=b.value;
		}

		Value(const T &b)
			:value(b)
		{
		}

		~Value()
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

		operator Matrix<T>()
		{
			return Matrix<T>(1, 1, value);
		}
		
		template <class U>
		friend class Value;
	};
}

