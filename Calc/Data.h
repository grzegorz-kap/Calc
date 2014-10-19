 #pragma once

#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

using std::shared_ptr;
using std::make_shared;

#include "UnimplementedException.h"
#include "CastException.h"


namespace PR
{
	template <class T>
	class Numeric;

	template <class T>
	class Value;

	class Token;
	class Output;

	enum class TYPE : int
	{
		TOKEN,
		OUTPUT,
		INT ,
		FLOAT,
		DOUBLE,
		C_INT,
		C_FLOAT,
		C_DOUBLE,
		M_INT,
		M_FLOAT,
		M_DOUBLE,
		CM_INT,
		CM_FLOAT,
		CM_DOUBLE
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

		virtual shared_ptr<Data> operator + (shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do addition on this type!");
		}

		virtual shared_ptr<Data> operator - (shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do subtraction on this type!");
		}

		virtual shared_ptr<Data> operator * (shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do multiplication on this type!");
		}

		virtual shared_ptr<Data> operator / (shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Can not do division on this type!");
		}

		virtual shared_ptr<Data> exponentiation(shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Cannot do exponentiation on this type!");
		}

		virtual shared_ptr<Data> mexponentiation(shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Cannot do matrix exponentiation on this type");
		}

		virtual shared_ptr<Data> operator - () const
		{
			throw UnimplementedException("Cannot do negation on this type!");
		}

		virtual shared_ptr<Data> times(shared_ptr<Data> &) const
		{
			throw UnimplementedException("Cannot do element wise multiplication on this type");
		}

		virtual shared_ptr<Data> rdivide(shared_ptr<Data> &) const
		{
			throw UnimplementedException("Cannot do right array division on this type");
		}

		virtual shared_ptr<Data> eq(shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Cannot do relational operator on this type");
		}

		virtual shared_ptr<Data> ge(shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Cannot do relational operator on this type");
		}

		virtual shared_ptr<Data> gt(shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Cannot do relational operator on this type");
		}

		virtual shared_ptr<Data> le(shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Cannot do relational operator on this type");
		}

		virtual shared_ptr<Data> lt(shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Cannot do relational operator on this type");
		}

		virtual shared_ptr<Data> ne(shared_ptr<Data> &b) const
		{
			throw UnimplementedException("Cannot do relational operator on this type");
		}

		virtual bool operator == (const bool &b) const
		{
			throw UnimplementedException("Cannot do bool eq on this type");
		}

		virtual string toString()
		{
			return string("");
		}

		virtual shared_ptr<Data> get_rows() const
		{
			throw UnimplementedException("Cannot do this on virtual type");
		}

		virtual shared_ptr<Data> get_cols() const
		{
			throw UnimplementedException("Cannot do this on virtual type");
		}

		virtual TYPE max_type() const
		{
			return _type;
		}

		template<class T>
		Numeric<T> * cast_numeric()
		{
			return dynamic_cast<Numeric<T> *> (this);
		}

		virtual Token * cast_token()
		{
			throw CastException("Cannot cast to Token");
		}

		virtual bool isNumeric() const
		{
			return false;
		}

		virtual bool isOutput() const
		{
			return false;
		}

		virtual Output * cast_output()
		{
			throw CastException("Cannot cast to Output");
		}


		template<class T>
		shared_ptr<Numeric<T>>  convert_numeric()
		{
			switch (this->_type)
			{
				case TYPE::M_DOUBLE:
					return make_shared<T>(*dynamic_cast<Matrix<double> *>(this));
				case TYPE::M_FLOAT:
					return make_shared<T>(*dynamic_cast<Matrix<float> *>(this));
				case TYPE::M_INT:
					return make_shared<T>(*dynamic_cast<Matrix<int> *>(this));
				case TYPE::DOUBLE:
					return make_shared<T>(*dynamic_cast<Value<double> *>(this));
				case TYPE::FLOAT:
					return make_shared<T>(*dynamic_cast<Value<float> *>(this));
				case TYPE::INT:
					return make_shared<T>(*dynamic_cast<Value<int> *> (this));

				default:
					throw CastException("Cannot cast to different numeric type! Probably not numeric type");
			}
		}
	};

};
