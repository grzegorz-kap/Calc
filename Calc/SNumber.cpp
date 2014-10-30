#include "stdafx.h"
#include "SNumber.h"


namespace PR
{
	SNumber::SNumber(Token &&token, TYPE type)
		:_type(type), Token(std::move(token))
	{
		_evType = TYPE::DOUBLE;
	}

	SNumber::SNumber(const Token &token, TYPE type)
		: _type(type), Token(token)
	{
		_evType = TYPE::DOUBLE;
	}


	SNumber::~SNumber()
	{
	}

	shared_ptr<Data> SNumber::evaluate()
	{
		switch (getEvType())
		{
		case TYPE::DOUBLE:
			return make_shared<ComplexNumber<double>>(getLexeme());
		case TYPE::M_DOUBLE:
			return make_shared< Matrix<double>>(getLexeme());
		case TYPE::R_DOUBLE:
			return make_shared<ComplexNumber<hdouble>>(getLexeme());
		case TYPE::RM_DOUBLE:
			return make_shared<Matrix<hdouble>>(getLexeme());
		default:
			throw EvalException("Cannot evaluate numeric expression! Unrecognized type",getPosition());
		}
	}
}