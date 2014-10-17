#pragma once

#include <string>
#include <memory>

#include "export.h"
#include "TokensTypes.h"
#include "CalcException.h"
#include "CastException.h"
#include "Data.h"


using std::string;
using std::shared_ptr;

namespace PR
{
	class Operator;
	class Assignment;

	enum class PARSE_MODE :char { NORMAL, FUNCTION, MATRIX,KEYWORD };

	class Token
		:public Data
	{
		string lexeme;
		TOKEN_CLASS _class;
		PARSE_MODE mode;
		int position;
		int param;
		int keyword_balance;
	public:

		Token();
		Token(const string &lexemeArg, TOKEN_CLASS typeArg, int position = 0,
			int param = 0,PARSE_MODE mode=PARSE_MODE::NORMAL);
		Token(TOKEN_CLASS arg);
		Token(Token &&);
		~Token();

		bool operator == (const Token &b)const;
		string getLexeme()const{ return lexeme; }
		const string & getLexemeR()const{ return lexeme; }
		void setLexeme(const string &lexemeArg){ lexeme = lexemeArg; }
		TOKEN_CLASS getClass() const { return _class; }
		void set_class(const TOKEN_CLASS &typeArg){ _class = typeArg; }
		int getPosition()const{ return position; }
		void setPosition(int pos){ position = pos; }
		int getParam() const { return param; }
		void setParam(int p){ param = p; }
		PARSE_MODE getMode()const { return mode; }
		void setMode(PARSE_MODE mode){ this->mode = mode; }
		void setKeywordBalance(int b){ keyword_balance = b; }
		int getKeywordBalance() const { return keyword_balance; }

		string toString() const;
		
		virtual shared_ptr<Data> evaluate()
		{
			throw 3.2;
		}

		virtual Operator * castToOperator() 
		{
			throw CastException("Cannot cast to operator expression");
		}

		virtual Assignment * castToAssignment()
		{
			throw CastException("Cannot cast to assignment target expression");
		}

		virtual Token* cast_token() override
		{
			return dynamic_cast<Token *>(this);
		}
	};
}