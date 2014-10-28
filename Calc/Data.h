 #pragma once
#include "export.h"

#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include <boost\multiprecision\cpp_bin_float.hpp>

using namespace boost::multiprecision;

using std::shared_ptr;
using std::make_shared;

#include "UnimplementedException.h"
#include "CastException.h"


namespace PR
{
	typedef cpp_bin_float_100 hdouble;

	template <class T>
	class Numeric;

	template <class T>
	class Matrix;

	template <class T>
	class ComplexNumber;

	class Token;
	class Output;

	enum class TYPE : int
	{
		UNKNOWN,
		TOKEN,
		OUTPUT,
		DOUBLE,
		R_DOUBLE,
		M_DOUBLE,
		RM_DOUBLE
	};

	class   Data
	{
	protected:
		
	public:
		Data();
		~Data();
		TYPE _type;
		
		const static std::unordered_map<std::type_index, TYPE> TYPE_MAP;
		const static std::unordered_map < TYPE, string > TYPE_NAME_MAP;

		static TYPE find_type(const std::type_index &idx);
		static const string & find_name(const TYPE &type);

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

		virtual shared_ptr<Data> transposition() const 
		{
			throw UnimplementedException("Cannot do transposition operator on this type");
		}

		virtual shared_ptr<Data> log() const
		{
			throw UnimplementedException("Cannot do 'log' on this type");
		}

		virtual shared_ptr<Data> log(shared_ptr<Data> &) const
		{
			throw UnimplementedException("Cannot do 'log' on this type");
		}

		virtual shared_ptr<Data> log2() const
		{
			throw UnimplementedException("Cannot do 'log2' on this type");
		}

		virtual shared_ptr<Data> log10() const
		{
			throw UnimplementedException("Cannot do 'log10' on this type");
		}

		virtual void lu(shared_ptr<Data> &) const
		{
			throw UnimplementedException("Cannot do 'lu' on this type");
		}

		virtual void  lu(shared_ptr<Data> &, shared_ptr<Data> &) const
		{
			throw UnimplementedException("Cannot do 'lu' on this type");
		}

		virtual void  lu(shared_ptr<Data> &, shared_ptr<Data> &, shared_ptr<Data> &) const
		{
			throw UnimplementedException("Cannot do 'lu' on this type");
		}

		virtual shared_ptr<Data> det() const
		{
			throw UnimplementedException("Cannot do 'det' on this type");
		}

		virtual shared_ptr<Data> sin() const
		{
			throw UnimplementedException("Cannot do 'sin' on this type");
		}

		virtual shared_ptr<Data> cos() const
		{
			throw UnimplementedException("Cannot do 'cos' on this type");
		}

		virtual shared_ptr<Data> tan() const
		{
			throw UnimplementedException("Cannot do 'tan' on this type");
		}

		virtual bool operator == (const bool &b) const
		{
			throw UnimplementedException("Cannot do bool eq on this type");
		}

		virtual string toString() const
		{
			return string("");
		}

		virtual string toHtml() const
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
				case TYPE::DOUBLE:
					return make_shared<T>(*dynamic_cast<ComplexNumber<double> *>(this));
				case TYPE::R_DOUBLE:
					return make_shared<T>(*dynamic_cast<ComplexNumber<hdouble> *>(this));
				case TYPE::RM_DOUBLE:
					return make_shared<T>(*dynamic_cast<Matrix<hdouble> *>(this));

				default:
					throw CastException("Cannot cast to different numeric type! Probably not numeric type");
			}
		}
	};

};
