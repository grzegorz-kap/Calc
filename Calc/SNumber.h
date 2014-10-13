#pragma once
#include "Token.h"
#include "Data.h"
#include "Value.h"
#include "Matrix.h"
#include "EvalException.h"

#include <memory>

using std::unique_ptr;

namespace PR
{
	class SNumber :
		public Token
	{
		TYPE _type;
	public:
		SNumber(Token &&token, TYPE type = TYPE::M_DOUBLE);
		SNumber(const Token &token, TYPE type = TYPE::M_DOUBLE);
		~SNumber();

		virtual shared_ptr<Data> evaluate() override;
	};
};