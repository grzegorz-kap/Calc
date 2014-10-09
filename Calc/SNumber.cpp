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

	Data * SNumber::eveluate()
	{
		switch (_type)
		{
		case TYPE::DOUBLE:
			return new Value<double>(getLexemeR());
		case TYPE::FLOAT:
			return new Value<float>(getLexemeR());
		case TYPE::INT:
			return new Value<int>(getLexemeR());
		case TYPE::M_DOUBLE:
			return new Matrix<double>(getLexemeR());
		case TYPE::M_FLOAT:
			return new Matrix<float>(getLexemeR());
		case TYPE::M_INT:
			return new Matrix<int>(getLexemeR());
		default:
			throw EvalException("Cannot evaluate numeric expression! Unrecognized type");
		}
	}
}