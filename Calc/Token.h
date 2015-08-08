#pragma once
#include <string>
#include <memory>
#include "TokensTypes.h"
#include "CalcException.h"
#include "CastException.h"
#include "Data.h"

using std::string;
using std::shared_ptr;

namespace KLab
{
	class Operator;
	class IAssignment;

	enum class PARSE_MODE :char { NORMAL, FUNCTION, MATRIX, KEYWORD };

	//! Klasa reprezentujaca symbol leksykalny.
	class Token :public Data
	{
	private:
		string lexeme;
		TOKEN_CLASS _class;
		PARSE_MODE mode;
		int position;
		int line;
		int param;
		int keyword_balance;
		int tree_level;
		int _arguments_num;

	protected:
		TYPE _evType;

	public:
		Token();
		Token(const string &lexemeArg, TOKEN_CLASS typeArg, int position = -1, int param = 0, PARSE_MODE mode = PARSE_MODE::NORMAL);
		Token(string &&lexemeArg, TOKEN_CLASS typeArg, int position = -1, int param = 0, PARSE_MODE mode = PARSE_MODE::NORMAL);
		Token(TOKEN_CLASS arg, int position = -1);
		Token(TOKEN_CLASS arg, int position, int paramA) :Token(arg, position) { param = paramA; }
		Token(Token &&);
		~Token();

		bool operator == (const Token &b)const;
		virtual string getLexeme()const;
		virtual const string & getLexemeR()const;
		void setLexeme(const string &lexemeArg);
		TOKEN_CLASS getClass() const;
		void set_class(const TOKEN_CLASS &typeArg);
		int getPosition()const;
		void setPosition(int pos);
		int getLine() const;
		void setLine(int line);
		int getParam() const;
		void setParam(int p);
		PARSE_MODE getMode()const;
		void setMode(PARSE_MODE mode);
		void setKeywordBalance(int b);
		int getKeywordBalance() const;
		TYPE getEvType()const;
		void setEvType(TYPE type);
		int getTreeLevel() const;
		void setTreeLevel(int arg);
		string toString() const;
		void argumentsNum(int n);
		int argumentsNum() const;
		virtual bool isToken(TOKEN_CLASS token_class) const override;
		virtual shared_ptr<Data> evaluate();
		virtual Operator * castToOperator();
		virtual IAssignment * castToAssignment();
		virtual Token* cast_token() override;

	private:
		void init();
	};
}