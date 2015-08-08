#include "stdafx.h"
#include "SNumber.h"

namespace KLab
{
	SNumber::SNumber(Token &&token, TYPE type)
		:_type(type), Token(std::move(token))
	{
		_evType = TYPE::DOUBLE;
		cache = nullptr;
	}

	SNumber::SNumber(const Token &token, TYPE type)
		: _type(type), Token(token)
	{
		_evType = TYPE::DOUBLE;
		cache = nullptr;
	}

	SNumber::~SNumber()
	{
	}

	shared_ptr<Data> SNumber::evaluate()
	{
		if (cache == nullptr)
			switch (getEvType())
		{
			case TYPE::DOUBLE:
				cache = make_shared<ComplexNumber<double>>(getLexeme());
				break;
			case TYPE::M_DOUBLE:
				cache = make_shared< Matrix<double>>(getLexeme());
				break;
			case TYPE::R_DOUBLE:
				cache = make_shared<ComplexNumber<hdouble>>(getLexeme());
				break;
			case TYPE::RM_DOUBLE:
				cache = make_shared<Matrix<hdouble>>(getLexeme());
				break;
			default:
				throw EvalException("Cannot evaluate numeric expression! Unrecognized type", getPosition());
		}
		return cache;
	}
}