#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

#include "CalcException.h"
#include "Token.h"

namespace PR
{


	class LexicalBalanceHelper
	{
		
	public:
		LexicalBalanceHelper();
		~LexicalBalanceHelper();

		void reset();
		void setMode(Token &token);
		PARSE_MODE getMode()const{ return mode.back(); }
	private:
		vector<int> balance;
		vector<PARSE_MODE> mode;
		int pos;

		void changeMode(PARSE_MODE mode, bool start);
		void onParenthesis(bool start);
	};

}
