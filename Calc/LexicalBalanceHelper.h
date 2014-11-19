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
		PARSE_MODE getMode()const;

		void throwOnUnbalancedEnd();
	private:
		
		vector<int> balance;
		vector<PARSE_MODE> mode;
		int pos;
		vector<TOKEN_CLASS> key_word_mode;
		int key_word_balance;

		void changeMode(PARSE_MODE mode, bool start);
		void onParenthesis(bool start);
		void onInstructionKeyWord(Token &token);
		void onEndKeyword(Token &token);
		void onContBreakKeyWords();
		void onFunction();
		void onFunctionEnd();
	};

}
