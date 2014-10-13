#pragma once

#include <string>


using std::string;

#include "Numeric.h"
#include "CastException.h"

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

		/*Unary minus operator*/
		Value<T> neg() const
		{
			return Value<T>(-value);
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
	};
};

