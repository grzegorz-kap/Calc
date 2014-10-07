#pragma once

#include <string>
#include <memory>

#include "export.h"
#include "TokensTypes.h"
#include "CalcException.h"


using std::string;
using std::shared_ptr;

namespace PR
{
	enum class PARSE_MODE :char { NORMAL, FUNCTION, MATRIX,KEYWORD };

	class Token
	{
		string lexeme;
		TOKEN_CLASS type;
		PARSE_MODE mode;
		int position;
		int param;
	public:
		Token();

		Token(string lexemeArg, TOKEN_CLASS typeArg, int position = 0,
			int param = 0,PARSE_MODE mode=PARSE_MODE::NORMAL);

		Token(TOKEN_CLASS arg);
		~Token();


		bool operator == (const Token &b)const;

		string getLexeme()const{ return lexeme; }
		const string & getLexemeR()const{ return lexeme; }
		void setLexeme(const string &lexemeArg){ lexeme = lexemeArg; }
		TOKEN_CLASS getType() const { return type; }
		void setType(const TOKEN_CLASS &typeArg){ type = typeArg; }
		int getPosition()const{ return position; }
		int getParam() const { return param; }
		void setParam(int p){ param = p; }
		PARSE_MODE getMode()const { return mode; }
		void setMode(PARSE_MODE mode){ this->mode = mode; }

		string toString() const;
		
	};
}