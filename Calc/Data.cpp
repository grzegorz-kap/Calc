#include "stdafx.h"
#include "Data.h"


namespace PR
{
	decltype(Data::TYPE_MAP) Data::TYPE_MAP =
	{
		{ typeid(Matrix<double>),TYPE::M_DOUBLE },
		{ typeid(ComplexNumber<double>),TYPE::DOUBLE },
		{ typeid(ComplexNumber<hdouble>), TYPE::R_DOUBLE },
		{ typeid(Matrix<hdouble>), TYPE::RM_DOUBLE }
	};

	decltype(Data::TYPE_NAME_MAP) Data::TYPE_NAME_MAP =
	{
		{ TYPE::M_DOUBLE, "Matrix<double>" },
		{ TYPE::RM_DOUBLE, "Matrix<mpf_float>" },
		{ TYPE::R_DOUBLE, "mpf_float" },
		{ TYPE::DOUBLE, "double" },
		{ TYPE::OUTPUT, "'function output'" },
		{ TYPE::UNKNOWN, "'unknown'" },
		{ TYPE::TOKEN, "'token'" }
	};

	Data::Data()
	{
	}

	Data::~Data()
	{
	}

	TYPE Data::find_type(const std::type_index &idx)
	{
		auto result = TYPE_MAP.find(idx);
		if (result != TYPE_MAP.end())
			return result->second;
		else
			return TYPE::UNKNOWN;
	}

	const string & Data::find_name(const TYPE &type)
	{
		return TYPE_NAME_MAP.find(type)->second;
	}

	shared_ptr<Data> Data::operator + (shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Can not do addition on this type!");
	}

	shared_ptr<Data> Data::operator - (shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Can not do subtraction on this type!");
	}

	shared_ptr<Data> Data::operator * (shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Can not do multiplication on this type!");
	}

	shared_ptr<Data> Data::operator / (shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Can not do division on this type!");
	}

	shared_ptr<Data> Data::exponentiation(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do exponentiation on this type!");
	}

	shared_ptr<Data> Data::mexponentiation(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do matrix exponentiation on this type");
	}

	shared_ptr<Data> Data::operator - () const
	{
		throw UnimplementedException("Cannot do negation on this type!");
	}

	shared_ptr<Data> Data::times(shared_ptr<Data> &) const
	{
		throw UnimplementedException("Cannot do element wise multiplication on this type");
	}

	shared_ptr<Data> Data::rdivide(shared_ptr<Data> &) const
	{
		throw UnimplementedException("Cannot do right array division on this type");
	}

	shared_ptr<Data> Data::eq(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do relational operator on this type");
	}

	shared_ptr<Data> Data::ge(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do relational operator on this type");
	}

	shared_ptr<Data> Data::gt(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do relational operator on this type");
	}

	shared_ptr<Data> Data::le(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do relational operator on this type");
	}

	shared_ptr<Data> Data::lt(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do relational operator on this type");
	}

	shared_ptr<Data> Data::ne(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do relational operator on this type");
	}

	shared_ptr<Data> Data::transposition() const
	{
		throw UnimplementedException("Cannot do transposition operator on this type");
	}

	shared_ptr<Data> Data::log() const
	{
		throw UnimplementedException("Cannot do 'log' on this type");
	}

	shared_ptr<Data> Data::log(shared_ptr<Data> &) const
	{
		throw UnimplementedException("Cannot do 'log' on this type");
	}

	shared_ptr<Data> Data::log2() const
	{
		throw UnimplementedException("Cannot do 'log2' on this type");
	}

	shared_ptr<Data> Data::log10() const
	{
		throw UnimplementedException("Cannot do 'log10' on this type");
	}

	void Data::lu(shared_ptr<Data> &) const
	{
		throw UnimplementedException("Cannot do 'lu' on this type");
	}

	void  Data::lu(shared_ptr<Data> &, shared_ptr<Data> &) const
	{
		throw UnimplementedException("Cannot do 'lu' on this type");
	}

	void  Data::lu(shared_ptr<Data> &, shared_ptr<Data> &, shared_ptr<Data> &) const
	{
		throw UnimplementedException("Cannot do 'lu' on this type");
	}

	shared_ptr<Data> Data::det() const
	{
		throw UnimplementedException("Cannot do 'det' on this type");
	}

	shared_ptr<Data> Data::inv() const
	{
		throw UnimplementedException("Cannot do 'inv' on this type");
	}

	shared_ptr<Data> Data::sin() const
	{
		throw UnimplementedException("Cannot do 'sin' on this type");
	}

	shared_ptr<Data> Data::cos() const
	{
		throw UnimplementedException("Cannot do 'cos' on this type");
	}

	shared_ptr<Data> Data::tan() const
	{
		throw UnimplementedException("Cannot do 'tan' on this type");
	}

	bool Data::operator == (const bool &b) const
	{
		throw UnimplementedException("Cannot do bool eq on this type");
	}

	string Data::toString() const
	{
		return string("");
	}

	string Data::toHtml() const
	{
		return string("");
	}

	shared_ptr<Data> Data::get_rows() const
	{
		throw UnimplementedException("Cannot do this on  type");
	}

	shared_ptr<Data> Data::get_cols() const
	{
		throw UnimplementedException("Cannot do this on  type");
	}

	TYPE Data::max_type() const
	{
		return _type;
	}

	Token * Data::cast_token()
	{
		throw CastException("Cannot cast to Token");
	}

	bool Data::isNumeric() const
	{
		return false;
	}

	bool Data::isOutput() const
	{
		return false;
	}

	Output * Data::cast_output()
	{
		throw CastException("Cannot cast to Output");
	}


}