#pragma once

#include <memory>

#include "Data.h"

using std::shared_ptr;

namespace PR
{
	/*
	Allowed types of veriables
	*/
	enum class TYPE : char
	{
		BOOL,
		CHAR,
		UINT,
		INT,
		LONG,
		FLOAT,
		DOUBLE,
		RATIONAL
	};

	/*
	Value<T> class declaration for virtual cast operator
	*/
	template <class T>
	class Value;

	/**
		Interface for numeric type data
	*/
	template <class T>
	class Numeric
		:public Data
	{
	public:
		Numeric() {};
		~Numeric() {};

		virtual bool numeric() const override final
		{
			return true;
		};

		template <class U>
		T* operator + (const Numeric<U> *b)
		{
			return new T(*derived_this() + *(b->derived_this()));
		}

		/*virtual operator Value<bool>() const = 0;
		virtual operator Value<char>() const = 0;
		virtual operator Value<unsigned int>() const = 0;
		virtual operator Value<int>() const = 0;
		virtual operator Value<long>() const = 0;
		virtual operator Value<float>() const = 0;
		virtual operator Value<double>() const = 0;*/

	public:
		TYPE _ty;
		const T* derived_this() const
		{
			return static_cast<const T*>(this);
		}

	};

}
