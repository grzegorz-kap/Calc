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

	shared_ptr<Data> SNumber::evaluate()
	{
		switch (_type)
		{
		case TYPE::DOUBLE:
			return make_shared<ComplexNumber<double>>(getLexemeR());
		case TYPE::M_DOUBLE:
			return make_shared< Matrix<double>>(getLexemeR());
		default:
			throw EvalException("Cannot evaluate numeric expression! Unrecognized type",getPosition());
		}
	}
}