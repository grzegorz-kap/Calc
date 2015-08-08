#include "stdafx.h"
#include "Token.h"

namespace KLab
{
	Token::Token(const string &lexame, TOKEN_CLASS tokenClass, int line /*= 0*/, int column /*= 0*/) {
		this->lexeme = lexeme;
		init(tokenClass, line, column);
	}

	Token::Token(string &&lexame, TOKEN_CLASS tokenClass, int line /*= 0*/, int column /*= 0*/) {
		this->lexeme = std::move(lexeme);
		init(tokenClass, line, column);
	}

	void Token::init(TOKEN_CLASS tokenClass, int line, int column) {
		this->column = column;
		this->line = line;
		this->tokenClass = tokenClass;
	}

	Token::~Token() {
	}

	bool Token::operator==(const Token &second) {
		return lexeme == second.lexeme && tokenClass == second.tokenClass;
	}

	string Token::getLexeme() const {
		return lexeme;
	}

	int Token::getLexemeLength() const {
		return (int)lexeme.length();
	}

	void Token::setLexeme(const string &lexemeArg) {
		lexeme = lexemeArg;
	}

	TOKEN_CLASS Token::getTokenClass() const {
		return tokenClass;
	}

	void Token::setTokenClass(const TOKEN_CLASS &typeArg) {
		tokenClass = typeArg;
	}

	int Token::getLine() const {
		return line;
	}

	void Token::setLine(int newLine) {
		line = newLine;
	}

	string::const_iterator Token::cbegin() const {
		return lexeme.cbegin();
	}

	string::const_iterator Token::cend() const {
		return lexeme.cend();
	}

	int Token::lastIndexOf(char c) const {
		return (int)lexeme.find_last_of(c);
	}

	int Token::getColumn()const {
		return column;
	}

	void Token::setColumn(int pos) {
		column = pos;
	}
}