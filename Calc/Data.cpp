#include "stdafx.h"
#include "Data.h"


namespace PR
{
	decltype(Data::TYPE_MAP) Data::TYPE_MAP =
	{
		{ typeid(Matrix<double>), TYPE::M_DOUBLE },
		{ typeid(ComplexNumber<double>), TYPE::DOUBLE },
		{ typeid(ComplexNumber<hdouble>), TYPE::R_DOUBLE },
		{ typeid(Matrix<hdouble>), TYPE::RM_DOUBLE },
		{ typeid(String),TYPE::STRING }
	};

	decltype(Data::TYPE_NAME_MAP) Data::TYPE_NAME_MAP =
	{
		{ TYPE::M_DOUBLE, "Matrix<double>" },
		{ TYPE::RM_DOUBLE, "Matrix<mpf_float>" },
		{ TYPE::R_DOUBLE, "mpf_float" },
		{ TYPE::DOUBLE, "double" },
		{ TYPE::OUTPUT, "'function output'" },
		{ TYPE::UNKNOWN, "'unknown'" },
		{ TYPE::TOKEN, "'token'" },
		{ TYPE::STRING, "'string'" }
	};

	Data::Data()
	{
		_type = TYPE::UNKNOWN;
		_added = false;
		_updated = false;
		_temp = true;
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

	shared_ptr<Data> Data::operator | (shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot execute logical | on this type.");
	}

	shared_ptr<Data> Data::operator & (shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot execute logical & on this type.");
	}

	shared_ptr<Data> Data::operator / (shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Can not do division on this type!");
	}

	shared_ptr<Data> Data::url (shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot solve URL on this type!");
	}

	shared_ptr<Data> Data::exponentiation(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do exponentiation on this type!");
	}

	shared_ptr<Data> Data::mexponentiation(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot do matrix exponentiation on this type");
	}

	shared_ptr<Data> Data::cfix() const
	{
		throw UnimplementedException("Cannot 'fix()' this type");
	}

	shared_ptr<Data> Data::cround() const
	{
		throw UnimplementedException("Cannot 'round()' this type");
	}

	shared_ptr<Data> Data::cfloor() const
	{
		throw UnimplementedException("Cannot 'floor()' this type");
	}

	shared_ptr<Data> Data::cmod(shared_ptr<Data> &b) const
	{
		throw UnimplementedException("Cannot 'mod' this types");
	}

	shared_ptr<Data> Data::cceil() const
	{
		throw UnimplementedException("Cannot 'ceil' this type");
	}

	shared_ptr<Data> Data::operator - () const
	{
		throw UnimplementedException("Cannot do negation on this type!");
	}

	shared_ptr<Data> Data::operator ! () const
	{
		throw UnimplementedException("Cannot do logical negation on this type!");
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

	shared_ptr<Data> Data::ctransposition() const
	{
		throw UnimplementedException("Cannot do conjugate transposition operator on this type");
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

	shared_ptr<Data> Data::conj() const
	{
		throw UnimplementedException("Cannot do 'conj' on this type");
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


	shared_ptr<Data> Data::cholesky() const
	{
		throw UnimplementedException("Cannot do 'chol' on this type");
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

	shared_ptr<Data> Data::cot() const
	{
		throw UnimplementedException("Cannot do 'cot' on this type");
	}

	shared_ptr<Data> Data::getAt() const
	{
		throw UnimplementedException("Cannot do 'at' on this type");
	}

	shared_ptr<Data> Data::copy() const
	{
		throw UnimplementedException("Cannot copy this data");
	}

	shared_ptr<Data> Data::getAt(shared_ptr<Data> &) const
	{
		throw UnimplementedException("Cannot do 'at' on this type");
	}

	shared_ptr<Data> Data::getAt(shared_ptr<Data> &m, shared_ptr<Data> &n) const
	{
		throw UnimplementedException("Cannot do 'at' on this type");
	}

	void Data::assignAt(shared_ptr<Data>& data)
	{
		throw UnimplementedException("Cannot do subscripted assignment eq on this type");
	}

	void Data::assignAt(shared_ptr<Data>& cells, shared_ptr<Data>& data)
	{
		throw UnimplementedException("Cannot do subscripted assignment eq on this type");
	}

	void Data::assignAt(shared_ptr<Data>& rows, shared_ptr<Data> & colls, shared_ptr<Data>& data)
	{
		throw UnimplementedException("Cannot do subscripted assignment eq on this type");
	}
	
	shared_ptr<Data> Data::createVector(shared_ptr<Data> &end) const
	{
		throw UnimplementedException("Wrong first operand for colon operator!");
	}
	
	shared_ptr<Data> Data::createVector(shared_ptr<Data> &step, shared_ptr<Data> &end) const
	{
		throw UnimplementedException("Wrong first operand for colon operator!");
	}

	bool Data::operator == (const bool &b) const
	{
		throw UnimplementedException("Cannot do bool eq on this type");
	}

	shared_ptr<Data> Data::getColumn(int idx) const
	{
		throw UnimplementedException("Get column is not supported on this type");
	}

	vector<double> Data::toDoubleVector() const
	{
		throw UnimplementedException("Undefined behaviour! toDoubleVector()");
	}

	vector<double> Data::toDoubleVectorAll() const
	{
		throw UnimplementedException("Undefined behaviour! toDoubleVector()");
	}

	shared_ptr<Data> Data::get_single_index() const
	{
		throw UnimplementedException("Cannot indexing this type");
	}

	shared_ptr<Data> Data::get_rows_index() const
	{
		throw UnimplementedException("Cannot indexing this type");
	}

	shared_ptr<Data> Data::get_cols_index() const
	{
		throw UnimplementedException("Cannot indexing this type");
	}


	string Data::minValueString() const
	{
		return "Unknown";
	}

	string Data::maxValueString() const
	{
		return "Unknown";
	}

	string Data::getValueInfoString() const
	{
		return "Unknown";
	}

	string Data::getTypeName() const
	{
		return TYPE_NAME_MAP.find(_type)->second;
	}

	string Data::toString() const
	{
		return string("");
	}

	string Data::toStringCommpact() const
	{
		return string("");
	}

	string Data::toHtml() const
	{
		return string("");
	}

	int Data::toInteger() const
	{
		throw UnimplementedException("Unimplemted 'toInteger()' function");
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

	string Data::prepareCastError()
	{
		return "Cannot convert '" + find_name(this->_type) + "' to numeric type";
	}


}