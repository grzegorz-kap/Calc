#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

#include "TokensTypes.h"
#include "Token.h"
#include "Operator.h"

namespace KLab
{
	class TokenizerHelper
	{
		const static unordered_map<string, TOKEN_CLASS> KEYWORDS;
	public:
		const static vector<TOKEN_CLASS> NO_STRING_PRECURSORS;

		static void toString(const vector<Token> &tokens, string &out);
		static bool isLetter(char c);
		static bool isDigit(char c);
		static bool isWhiteSpace(char c);
		static bool isKeyWord(const string &word);
		static TOKEN_CLASS keyWordOrId(const string &word);
	private:
		TokenizerHelper() = delete;
		~TokenizerHelper() = delete;
	};
}
