 #pragma once

#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

using std::unique_ptr;
using std::make_unique;

#include "UnimplementedException.h"

namespace PR
{
	template <class T>
	class Numeric;

	enum class TYPE : char
	{
		M_INT,
		M_FLOAT,
		M_DOUBLE
	};

	class Data
	{
	protected:
		TYPE _type;
	public:
		Data();
		~Data();

		static std::unordered_map<std::type_index, TYPE> TYPE_MAP;
		static bool TYPE_MAP_BUILDED;

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
		unique_ptr<Numeric<T>>  cast_numeric()
		{
			auto pointer = dynamic_cast<Numeric<T> *> (this);
			
			if (pointer)
				return unique_ptr<Numeric<T>>(pointer);

			switch (this->_type)
			{
				case TYPE::M_DOUBLE:
				{
					auto pointer = dynamic_cast<Matrix<double> *>(this);
					//T *converted_pointer = new T(*pointer);
					return make_unique<T>(*pointer);
				}
					break;
			}
		}
	};

}
