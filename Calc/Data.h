#pragma once

#include <memory>

using std::unique_ptr;

#include "UnimplementedException.h"

namespace PR
{
	template <class T>
	class Numeric;

	class Data
	{
	public:
		Data();
		~Data();

		virtual unique_ptr<Data> operator + (const unique_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do addition on this type!");
		}

		virtual unique_ptr<Data> operator - (const unique_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do subtraction on this type!");
		}

		virtual unique_ptr<Data> operator * (const unique_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do multiplication on this type!");
		}

		virtual unique_ptr<Data> operator / (const unique_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do division on this type!");
		}

		virtual bool isMatrix() const
		{
			return false;
		}

		virtual bool isScalar() const
		{
			return false;
		}

		template<class T>
		Numeric<T> * cast_numeric()
		{
			auto temp = dynamic_cast<Numeric<T> *>(this);

			if (temp)
				return temp;

			Numeric<T> val = *this;
		}
	};

}
