 #pragma once

#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

using std::unique_ptr;
using std::make_unique;

#include "UnimplementedException.h"
#include "CastException.h"

namespace PR
{
	template <class T>
	class Numeric;

	enum class TYPE : char
	{
		M_INT,
		M_FLOAT,
		M_DOUBLE,
		INT,
		FLOAT,
		DOUBLE
	};

	class Data
	{
	protected:
		
	public:
		Data();
		~Data();
		TYPE _type;
		static std::unordered_map<std::type_index, TYPE> TYPE_MAP;
		static std::unordered_map < TYPE, string > TYPE_NAME_MAP;
		static bool TYPE_MAP_BUILDED;

		virtual unique_ptr<Data> operator + (unique_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do addition on this type!");
		}

		virtual unique_ptr<Data> operator - (unique_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do subtraction on this type!");
		}

		virtual unique_ptr<Data> operator * (unique_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do multiplication on this type!");
		}

		virtual unique_ptr<Data> operator / (unique_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do division on this type!");
		}

		virtual string toString()
		{
			return string("");
		}

		template<class T>
		Numeric<T> * cast_numeric()
		{
			return dynamic_cast<Numeric<T> *> (this);
		}

		template<class T>
		unique_ptr<Numeric<T>>  convert_numeric()
		{
			switch (this->_type)
			{
				case TYPE::M_DOUBLE:
					return make_unique<T>(*dynamic_cast<Matrix<double> *>(this));
				case TYPE::M_FLOAT:
					return make_unique<T>(*dynamic_cast<Matrix<float> *>(this));
				case TYPE::M_INT:
					return make_unique<T>(*dynamic_cast<Matrix<int> *>(this));
				case TYPE::DOUBLE:
					return make_unique<T>(*dynamic_cast<Value<double> *>(this));
				case TYPE::FLOAT:
					return make_unique<T>(*dynamic_cast<Value<float> *>(this));
				case TYPE::INT:
					return make_unique<T>(*dynamic_cast<Value<int> *> (this));
				default:
					throw CastException("Cannot cast to different numeric type! Probably not numeric type");
			}
		}
	};

}
