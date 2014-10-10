#include "stdafx.h"
#include "SNumber.h"


namespace PR
{
	int SNumber::i = 0;

	SNumber::SNumber(Token &&token, TYPE type)
		:_type(type), Token(std::move(token))
	{
		set();
	}

	SNumber::SNumber(const Token &token, TYPE type)
		: _type(type), Token(token)
	{
		set();
	}


	SNumber::~SNumber()
	{
	}

	shared_ptr<Data> SNumber::evaluate()
	{
		switch (_type)
		{
		case TYPE::DOUBLE:
			return make_shared<Value<double>>(getLexemeR());
		case TYPE::FLOAT:
			return make_shared<Value<float>>(getLexemeR());
		case TYPE::INT:
			return make_shared< Value<int>>(getLexemeR());
		case TYPE::M_DOUBLE:
			return make_shared< Matrix<double>>(getLexemeR());
		case TYPE::M_FLOAT:
			return make_shared<Matrix<float>>(getLexemeR());
		case TYPE::M_INT:
			return make_shared<Matrix<int>>(getLexemeR());
		default:
			throw EvalException("Cannot evaluate numeric expression! Unrecognized type");
		}
	}
}