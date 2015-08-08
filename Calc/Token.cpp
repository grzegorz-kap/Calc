#include "stdafx.h"
#include "Token.h"

namespace KLab
{
	Token::Token()
	{
		init();
	}

	Token::Token(const string &tokenArg, TOKEN_CLASS typeArg, int position, int param, PARSE_MODE mode)
		:lexeme(tokenArg), _class(typeArg), position(position), param(param), mode(mode)
	{
		init();
	}

	Token::Token(string &&tokenArg, TOKEN_CLASS typeArg, int position, int param, PARSE_MODE mode)
		: lexeme(std::move(tokenArg)), _class(typeArg), position(position), param(param), mode(mode)
	{
		init();
	}

	Token::Token(TOKEN_CLASS arg, int position)
		: _class(arg),
		position(position)
	{
		init();
	}

	void Token::init()
	{
		_type = TYPE::TOKEN;
		_evType = TYPE::TOKEN;
		tree_level = -1;
		line = 0;
		position = 1;
	}

	Token::Token(Token &&b)
	{
		lexeme = std::move(b.lexeme);
		_class = b._class;
		position = b.position;
		param = b.param;
		mode = b.mode;
		_evType = b._evType;
		tree_level = b.tree_level;

		b._class = TOKEN_CLASS::NONE;
		b.position = 0;
		b.param = 0;
		b.mode = PARSE_MODE::NORMAL;
		b._evType = TYPE::DOUBLE;
		b.tree_level = -1;
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

	string Token::getLexeme() const
	{
		return lexeme;
	}

	const string & Token::getLexemeR() const
	{
		return lexeme;
	}

	void Token::setLexeme(const string &lexemeArg)
	{
		lexeme = lexemeArg;
	}

	TOKEN_CLASS Token::getClass() const
	{
		return _class;
	}

	void Token::set_class(const TOKEN_CLASS &typeArg)
	{
		_class = typeArg;
	}

	int Token::getLine() const
	{
		return line;
	}

	void Token::setLine(int newLine)
	{
		line = newLine;
	}

	int Token::getPosition()const
	{
		return position;
	}

	void Token::setPosition(int pos)
	{
		position = pos;
	}

	int Token::getParam() const
	{
		return param;
	}

	void Token::setParam(int p)
	{
		param = p;
	}

	PARSE_MODE Token::getMode()const
	{
		return mode;
	}

	void Token::argumentsNum(int n)
	{
		_arguments_num = n;
	}

	int Token::argumentsNum() const
	{
		return _arguments_num;
	}

	void Token::setMode(PARSE_MODE mode)
	{
		this->mode = mode;
	}

	void Token::setKeywordBalance(int b)
	{
		keyword_balance = b;
	}

	int Token::getKeywordBalance() const
	{
		return keyword_balance;
	}

	TYPE Token::getEvType()const
	{
		return _evType;
	}

	void Token::setEvType(TYPE type)
	{
		_evType = type;
	}

	int Token::getTreeLevel() const
	{
		return tree_level;
	}

	void Token::setTreeLevel(int arg)
	{
		tree_level = arg;
	}

	bool Token::isToken(TOKEN_CLASS token_class) const
	{
		return _class == token_class;
	}

	shared_ptr<Data> Token::evaluate()
	{
		throw CalcException("Cannot evaulate this expression! " + lexeme, position);
	}

	Operator * Token::castToOperator()
	{
		throw CastException("Cannot cast to operator expression");
	}

	IAssignment * Token::castToAssignment()
	{
		throw CastException("Cannot cast to assignment target expression");
	}

	Token* Token::cast_token()
	{
		return dynamic_cast<Token *>(this);
	}
}