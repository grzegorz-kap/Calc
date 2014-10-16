#include "stdafx.h"
#include "TokenizerHelper.h"

namespace PR
{
	/*const vector<string> TokenizerHelper::KEYWORDS = {
		"if", "for", "while", "continue", "break"
	};*/
	const unordered_map<string,TOKEN_CLASS> TokenizerHelper::KEYWORDS = 
	{
		{ "if",TOKEN_CLASS::IF_KEYWORD },
		{ "for",TOKEN_CLASS::FOR_KEYWORD },
		{ "while",TOKEN_CLASS::WHILE_KEYWORD },
		{ "continue",TOKEN_CLASS::CONTINUE_KEYWORD },
		{ "break",TOKEN_CLASS::BREAK_KEYWORD },
		{ "end",TOKEN_CLASS::END_KEYWORD },
		{ "else",TOKEN_CLASS::ELSE_KEYWORD }
	};

	bool TokenizerHelper::isKeyWord(const string &word)
	{
		return TokenizerHelper::KEYWORDS.find(word) != TokenizerHelper::KEYWORDS.end();
	}

	TOKEN_CLASS TokenizerHelper::keyWordOrId(const string &word)
	{
		auto result = TokenizerHelper::KEYWORDS.find(word);
		if (result != TokenizerHelper::KEYWORDS.end())
			return result->second;
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

