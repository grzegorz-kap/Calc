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

		virtual shared_ptr<Data> operator + (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator - (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator * (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator / (shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> exponentiation(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> mexponentiation(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> operator - () const;
		virtual shared_ptr<Data> times(shared_ptr<Data> &) const;
		virtual shared_ptr<Data> rdivide(shared_ptr<Data> &) const;
		virtual shared_ptr<Data> eq(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> ge(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> gt(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> le(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> lt(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> ne(shared_ptr<Data> &b) const;
		virtual shared_ptr<Data> transposition() const;
		virtual shared_ptr<Data> log() const;
		virtual shared_ptr<Data> log(shared_ptr<Data> &) const;
		virtual shared_ptr<Data> log2() const;
		virtual shared_ptr<Data> log10() const;
		virtual void lu(shared_ptr<Data> &) const;
		virtual void  lu(shared_ptr<Data> &, shared_ptr<Data> &) const;
		virtual void  lu(shared_ptr<Data> &, shared_ptr<Data> &, shared_ptr<Data> &) const;
		virtual shared_ptr<Data> det() const;
		virtual shared_ptr<Data> inv() const;
		virtual shared_ptr<Data> sin() const;
		virtual shared_ptr<Data> cos() const;
		virtual shared_ptr<Data> tan() const;
		virtual bool operator == (const bool &b) const;
		virtual string toString() const;
		virtual string toHtml() const;
		virtual shared_ptr<Data> get_rows() const;
		virtual shared_ptr<Data> get_cols() const;
		virtual TYPE max_type() const;
		virtual Token * cast_token();
		virtual bool isNumeric() const;
		virtual bool isOutput() const;
		virtual shared_ptr<Data> getAt() const;
		virtual shared_ptr<Data> getAt(shared_ptr<Data>&) const;
		virtual shared_ptr<Data> getAt(shared_ptr<Data>&, shared_ptr<Data>&) const;
		virtual Output * cast_output();

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

		template<class T>
		Numeric<T> * cast_numeric()
		{
			return dynamic_cast<Numeric<T> *> (this);
		}
		
	};

};
