#pragma once

#include <string>


using std::string;

#include "Numeric.h"
#include "CastException.h"

namespace PR
{
	template<class Z>
	class Matrix;

	class Output;
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

		Value(const string &string)
		{
			std::size_t pos = 0;
			_type = Data::TYPE_MAP[typeid(*this)];
			try{
				value = (T)std::stod(string, &pos);
			}
			catch (...)
			{
				throw CastException("String to numeric - invalid argument or out of range!");
			}

			if (pos < string.size())
				throw CastException("Cannot convert std::string to numeric type");
		}

		virtual ~Value()
		{
		}

		Value<T> rows() const
		{
			return Value<T>(1);
		}

		Value<T> cols() const
		{
			return Value<T>(1);
		}

		virtual bool operator == (const bool &b) const override
		{
			return value != 0;
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

		/* Right array division */
		template <class U>
		auto rdivide(const Value<U> &b) const
			->Value < decltype(T()/U()) >
		{
			return Value<decltype(T() / U())>(value / b.value);
		}

		/* Left array division */
		template <class U>
		auto ldivide(const Value<U> &b) const
			->Value < decltype(T() + U()) >
		{
			return Value<decltype(T() + U())>(b.value / value);
		}

		/*Element wise multiplication*/
		template <class U>
		auto times(const Value<U> &b) const
			->Value < decltype(T()*U()) >
		{
			return Value<decltype(T() * U())>(value * b.value);
		}

		/*Unary minus operator*/
		Value<T> neg() const
		{
			return Value<T>(-value);
		}

		template <class U>
		auto operator == (const Value<U> &b) const
			->Value < decltype(T() + U()) >
		{
			return Value<decltype(T() + U())>(value == b.value);
		}

		template <class U>
		auto operator != (const Value<U> &b) const
			->Value < decltype(T() + U()) >
		{
			return Value<decltype(T() + U())>(value != b.value);
		}

		template <class U>
		auto operator >= (const Value<U> &b) const
			->Value < decltype(T() + U()) >
		{
			return Value<decltype(T() + U())>(value >= b.value);
		}

		template <class U>
		auto operator > (const Value<U> &b) const
			->Value < decltype(T() + U()) >
		{
			return Value<decltype(T() + U())>(value > b.value);
		}

		template <class U>
		auto operator <= (const Value<U> &b) const
			->Value < decltype(T() + U()) >
		{
			return Value<decltype(T() + U())>(value <= b.value);
		}

		template <class U>
		auto operator < (const Value<U> &b) const
			->Value < decltype(T() + U()) >
		{
			return Value<decltype(T() + U())>(value < b.value);
		}

		Value<T> transpose() const
		{
			return Value<T>(value);
		}

		template <class X>
		operator Value<X>()
		{
			return Value<X>((X) value);
		}

		template <class X>
		operator Matrix<X>()
		{
			return Matrix<X>((X)value);
		}

		template <class X>
		operator X()
		{
			return X(value);
		}
		
		template <class U>
		friend class Value;

		friend class Math;
	};
};

