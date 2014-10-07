#include "stdafx.h"
#include "Token.h"

namespace PR
{
	Token::Token()
	{
		_ty = DATA_TYPE::TOKEN;
	}

	Token::Token(string tokenArg, TOKEN_CLASS typeArg, int position ,int param,PARSE_MODE mode,DATA_TYPE evalType)
		:lexeme(tokenArg), type(typeArg), position(position), param(param), mode(mode), evalType(evalType)
	{
		_ty = DATA_TYPE::TOKEN;
	}

	Token::Token(TOKEN_CLASS arg)
		: Token()
	{
		_ty = DATA_TYPE::TOKEN;
		type = arg;
	}

	Token::~Token()
	{
	}

	shared_ptr<Data> Token::evaluate(STACK &)
	{
		throw CalcException("Can not evaluate this symbol", position);
	}

	shared_ptr<Token> Token::cast(const shared_ptr<Data> &b,bool exs)
	{
		auto temp = std::dynamic_pointer_cast<Token>(b);

		if (exs&& temp == nullptr)
			throw CalcException("Cannot cast to 'Token' type");

		return temp;
	}

	bool Token::operator==(const Token &b) const
	{
		if (lexeme != b.lexeme)
			return false;
		if (type != b.type)
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
		else if (type == TOKEN_CLASS::FUNCTON_ARGS_END)
			out.append("$FUNC_ARGS_END");
		else if (type == TOKEN_CLASS::VERSE_END)
			out.append("$WE");
		else if (type == TOKEN_CLASS::MATRIX_ALL)
			out.append("$:");
		else
			out.append(lexeme);

		out.append("\t" + std::to_string(type));
		out.append("\t" + std::to_string(position));
		return out;
	}

}