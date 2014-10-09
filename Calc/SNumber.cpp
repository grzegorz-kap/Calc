#include "stdafx.h"
#include "SNumber.h"


namespace PR
{
	SNumber::SNumber(Token &&token, TYPE type)
		:_type(type), Token(std::move(token))
	{
	}

	SNumber::SNumber(const Token &token, TYPE type)
		: _type(type), Token(token)
	{
	}


	SNumber::~SNumber()
	{
	}

	unique_ptr<Data> SNumber::evaluate()
	{
		switch (_type)
		{
		case TYPE::DOUBLE:
			return make_unique<Value<double>>(getLexemeR());
		case TYPE::FLOAT:
			return make_unique<Value<float>>(getLexemeR());
		case TYPE::INT:
			return make_unique< Value<int>>(getLexemeR());
		case TYPE::M_DOUBLE:
			return make_unique< Matrix<double>>(getLexemeR());
		case TYPE::M_FLOAT:
			return make_unique<Matrix<float>>(getLexemeR());
		case TYPE::M_INT:
			return make_unique<Matrix<int>>(getLexemeR());
		default:
			throw EvalException("Cannot evaluate numeric expression! Unrecognized type");
		}
	}
}