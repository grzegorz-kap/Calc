#pragma once

#include "commons.h"

#include "TokenClass.h"

using std::string;

namespace KLab
{
	class Token {
	private:
		string lexeme;
		TOKEN_CLASS tokenClass;
		int column;
		int line;

	public:
		Token(const string &lexame, TOKEN_CLASS tokenClass, int line = 0, int column = 0);
		Token(string &&lexame, TOKEN_CLASS tokenClass, int line = 0, int column = 0);
		~Token();

		bool operator == (const Token &second);

		string getLexeme() const;
		int getLexemeLength() const;
		void setLexeme(const string &lexeme);
		TOKEN_CLASS getTokenClass() const;
		void setTokenClass(const TOKEN_CLASS &typeArg);
		int getColumn()const;
		void setColumn(int pos);
		int getLine() const;
		void setLine(int line);
		string::const_iterator cbegin() const;
		string::const_iterator cend() const;
		int lastIndexOf(char c)const;

	private:
		void init(TOKEN_CLASS tokenClass, int line, int column);
	};
}