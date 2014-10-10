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
		static int i;

		void set()
		{
			SNumber::i++;
			switch (SNumber::i % 3)
			{
			case 0: _type = TYPE::M_DOUBLE; break;
			case 1: _type = TYPE::INT; break;
			case 2: _type = TYPE::M_FLOAT; break;
			}
		}
	public:
		SNumber(Token &&token, TYPE type = TYPE::M_DOUBLE);
		SNumber(const Token &token, TYPE type = TYPE::M_DOUBLE);
		~SNumber();

		virtual shared_ptr<Data> evaluate() override;
	};
};