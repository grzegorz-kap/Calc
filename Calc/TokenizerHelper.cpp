#include "stdafx.h"
#include "TokenizerHelper.h"

namespace PR
{
	const vector<string> TokenizerHelper::KEYWORDS = {
		"if", "for", "while", "continue", "break"
	};

	bool TokenizerHelper::isKeyWord(const string &word)
	{
		return TokenizerHelper::KEYWORDS.end()!= std::find(TokenizerHelper::KEYWORDS.begin(), TokenizerHelper::KEYWORDS.end(), word);
	}

	TOKEN_CLASS TokenizerHelper::keyWordOrId(const string &word)
	{
		if (TokenizerHelper::isKeyWord(word))
			return TOKEN_CLASS::KEY_WORD;
		else
			return TOKEN_CLASS::ID;
	}

	bool TokenizerHelper::isLetter(char c)
	{
		return c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z' || c == '_';
	}

	bool TokenizerHelper::isDigit(char c)
	{
		return c >= '0' && c <= '9';
	}

	bool TokenizerHelper::isWhiteSpace(char c)
	{
		return c == ' ' || c == '\n' || c == '\t' || c == '\r';
	}

	//bool TokenizerHelper::isOperator(const string &str, int start_p){}

	void TokenizerHelper::toString(const vector<Token> &tokens, string &out)
	{
		out = "";
		for (const Token &v : tokens)
		{
			out.append(v.toString() + "\n");
		}
	}
}

