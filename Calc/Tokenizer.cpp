 #include "stdafx.h"
#include "Tokenizer.h"

namespace PR
{
	const vector<TOKEN_CLASS> Tokenizer::FOR_SPACE_DELETE = {
		TOKEN_CLASS::NEW_LINE,  TOKEN_CLASS::OPEN_PARENTHESIS,
		TOKEN_CLASS::CLOSE_PARENTHESIS, TOKEN_CLASS::SPACE, TOKEN_CLASS::COLON,
		TOKEN_CLASS::SEMICOLON, TOKEN_CLASS::COMMA, TOKEN_CLASS::IF_KEYWORD, FOR_KEYWORD,
		TOKEN_CLASS::WHILE_KEYWORD, TOKEN_CLASS::CONTINUE_KEYWORD, TOKEN_CLASS::BREAK_KEYWORD, TOKEN_CLASS::END_KEYWORD,
		TOKEN_CLASS::FUNCTION_KEYWORD,TOKEN_CLASS::OPERATOR
	};

	const vector<string> Tokenizer::END_SYNONIMS = {
		"endfor", "endif", "endwhile", "endfunction"
	};

	Tokenizer::Tokenizer()
	{
		N = 0;
		i = 0;
	}

    Tokenizer::~Tokenizer()
	{
	}

	void Tokenizer::setInput(const string &in)
	{
		command = in;
		init();
	}

	void Tokenizer::setInput(string &&in)
	{
		command = std::move(in);
		init();
	}

	void Tokenizer::readOthers()
	{
		TOKEN_CLASS type;
		char znak = command[i];
		switch (command[i])
		{
		case '(':
			type = TOKEN_CLASS::OPEN_PARENTHESIS;
			break;
		case ')':
			type =  TOKEN_CLASS::CLOSE_PARENTHESIS;
			break;
		case '[':
			type = TOKEN_CLASS::MATRIX_START;
			break;
		case ']':
			type = TOKEN_CLASS::MATRIX_END;
			break;
		case ':':
			type = TOKEN_CLASS::COLON;
			break;
		case ';':
			type =  TOKEN_CLASS::SEMICOLON;
			break;
		case ',':
			type = TOKEN_CLASS::COMMA;
			break;
		default:
			throw CalcException("Unrecognized symbol", i);
		}
		tokens.push_back(make_unique<Token>( type,i++));
	}

	bool Tokenizer::readOperator()
	{
		if (command[i]=='\''&&!find(TokenizerHelper::NO_STRING_PRECURSORS, prev())&&prevChar()!='.')
		{
			readString();
			return true;
		}

		auto result = OperatorsFactory::get(command, i);
		if (result != nullptr)
		{
			result->setPosition(i);
			i += result->getLexemeR().size();
			tokens.push_back(std::move(result));
			return true;
		}
		return false;
	}

	void Tokenizer::readNumber()
	{
		string out;
		NumberReader::read(command, out, i);
		int m = out.size();
		tokens.push_back(make_unique<SNumber>(Token(std::move(out), TOKEN_CLASS::NUMBER, i)));
		i += m;
	}

	void Tokenizer::readWord()
	{
		int start = i;
		string lexame="";
		while (i < N && (TokenizerHelper::isLetter(command[i]) || TokenizerHelper::isDigit(command[i])))
			lexame += command[i++];
		
		if (std::find(END_SYNONIMS.cbegin(), END_SYNONIMS.cend(), lexame) != END_SYNONIMS.end())
			lexame = "end";

		auto _class = TokenizerHelper::keyWordOrId(lexame);
		if (i < N&& command[i] == '(')
		{
			if (_class != TOKEN_CLASS::ID)
				throw CalcException("Unexpected open parenthesis!", i);
			_class = TOKEN_CLASS::FUNCTION;
		}

		tokens.push_back(make_unique<Token>(std::move(lexame), _class, start));
	}

	void Tokenizer::readString()
	{
		int start = i++;
		string lexame = "";
		bool found = false;
		while (i < N && command[i]!='\n')
		{
			if (command[i] == '\'')
			{
				if (i < N - 1 && command[i + 1] == '\'')
				{
					i += 2;
					lexame += '\'';
					continue;
				}
				found = true;
				i++;
				break;
			}
			lexame += command[i++];
		}

		if (!found)
			throw CalcException(" A MATLAB string constant is not terminated properly.", start);

		unique_ptr<String> token = make_unique<String>(std::move(lexame));
		token->setPosition(start);
		tokens.push_back(std::move(token));
	}

	void Tokenizer::readWhiteSpace()
	{
		switch (command[i])
		{
		case '\n':
			tokens.push_back(make_unique<Token>("\n", TOKEN_CLASS::NEW_LINE, i++));
			break;
		case '\t':
		case ' ':
		case '\r':
			if (tokens.size()!=0 && !find(FOR_SPACE_DELETE, tokens.back()->getClass()))
				tokens.push_back(make_unique<Token>(TOKEN_CLASS::SPACE, i));
			i++;
			break;
		}
	}

	void Tokenizer::skipBlockComment()
	{
		while (i < N - 1)
			if (command[i] == '*'&&command[i + 1] == '/')
				break;
			else
				i++;
		i += 2;
	}

	void Tokenizer::skipLineComment()
	{
		while (i < N)
			if (command[i++] == '\n')break;
	}

	void Tokenizer::deleteUneccessary()
	{
		if (i < N)
		{
			char z = command[i];
			if (i < N - 1 && z == '/' && command[i + 1] == '*')
			{
				skipBlockComment();
				deleteUneccessary();
			}
			else if (z == '%' || (i < N - 1 && z == '/'&&command[i + 1] == '/'))
			{
				skipLineComment();
				deleteUneccessary();
			}
			else if ((z == '\n' && (prev() == TOKEN_CLASS::NEW_LINE  || prev() == TOKEN_CLASS::SEMICOLON)) ||(i < N - 1 && z == '\n'&&z == ';'))
			{
				i++;
				deleteUneccessary();
			}
		}
	}

	void Tokenizer::tokenize()
	{	
		deleteUneccessary();
		while (i < N)
		{
			if (TokenizerHelper::isDigit(command[i]))
				readNumber();
			else if (TokenizerHelper::isLetter(command[i]))
				readWord();
			else if (TokenizerHelper::isWhiteSpace(command[i]))
				readWhiteSpace();
			else if (readOperator())
				continue;
			else readOthers();
			deleteUneccessary();
		}
	}

	void Tokenizer::whiteSpacesBegin()
	{
		while (i < N&&TokenizerHelper::isWhiteSpace(command[i]))
			i++;
	}

	void Tokenizer::whiteSpacesEnd()
	{
		while (N > 0 && TokenizerHelper::isWhiteSpace(command[N - 1]))
			N--;
	}

	vector<unique_ptr<Token>> Tokenizer::getTokens()
	{
		return std::move(tokens);
	}

	TOKEN_CLASS Tokenizer::prev()
	{
		if (tokens.size() == 0)
			return TOKEN_CLASS::NONE;
		return tokens.back()->getClass();
	}

	void Tokenizer::init()
	{
		N = command.size();
		i = 0;
		whiteSpacesEnd();
		whiteSpacesBegin();
	}

	char Tokenizer::prevChar()
	{
		if (i == 0)
			return 0;
		return command[i - 1];
	}
}