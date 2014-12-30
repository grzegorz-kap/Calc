#pragma once
#include "Token.h"
#include "Data.h"
#include "Matrix.h"
#include "ComplexNumber.h"
#include "EvalException.h"

#include <memory>

using std::unique_ptr;

namespace PR
{
	class SNumber :
		public Token
	{
		TYPE _type;
		shared_ptr<Data> cache;
	public:
		SNumber(Token &&token, TYPE type = TYPE::DOUBLE);
		SNumber(const Token &token, TYPE type = TYPE::DOUBLE);
		~SNumber();

		virtual shared_ptr<Data> evaluate() override;
	};
};