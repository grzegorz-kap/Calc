#include "stdafx.h"
#include "Token.h"

namespace PR
{
	Token::Token()
	{
	}

	Token::Token(string tokenArg, TOKEN_CLASS typeArg, int position ,int param,PARSE_MODE mode)
		:lexeme(tokenArg), _class(typeArg), position(position), param(param), mode(mode)
	{
	}

	Token::Token(TOKEN_CLASS arg)
		: Token()
	{
		_class = arg;
	}

	Token::~Token()
	{
	}


	bool Token::operator==(const Token &b) const
	{
		if (lexeme != b.lexeme)
			return false;
		if (_class != b._class)
			return false;
		return true;
	}

	string Token::toString() const
	{
		string out = "";
		if (lexeme == "\n")
			out.append("$NEW_LINE");
		else if (lexeme == "\t")
			out.append("$TABULATOR");
		else if (lexeme == " ")
			out.append("$SPACE");
		else if (_class == TOKEN_CLASS::FUNCTON_ARGS_END)
			out.append("$FUNC_ARGS_END");
		else if (_class == TOKEN_CLASS::VERSE_END)
			out.append("$WE");
		else if (_class == TOKEN_CLASS::MATRIX_ALL)
			out.append("$:");
		else
			out.append(lexeme);

		out.append("\t" + std::to_string(_class));
		out.append("\t" + std::to_string(position));
		return out;
	}

}