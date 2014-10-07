#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "TokensTypes.h"
#include "Token.h"
#include "Operator.h"

namespace PR
{
	class TokenizerHelper
	{

	public:
		const static vector<string> KEYWORDS;

		static void toString(const vector<Token> &tokens, string &out);
		static bool isLetter(char c);
		static bool isDigit(char c);
		static bool isWhiteSpace(char c);
		static bool isKeyWord(const string &word);
	//	static bool isOperator(const string &word, int start_p = 0);
		static TOKEN_CLASS keyWordOrId(const string &word);
	private:
		TokenizerHelper() = delete;
		~TokenizerHelper() = delete;

	};
}

