 #include "stdafx.h"
#include "Tokenizer.h"

namespace PR
{
	const vector<TOKEN_CLASS> Tokenizer::FOR_SPACE_DELETE = {
		TOKEN_CLASS::NEW_LINE, TOKEN_CLASS::OPERATOR, TOKEN_CLASS::OPEN_PARENTHESIS,
		TOKEN_CLASS::CLOSE_PARENTHESIS, TOKEN_CLASS::SPACE, TOKEN_CLASS::COLON,
		TOKEN_CLASS::SEMICOLON, TOKEN_CLASS::COMMA, TOKEN_CLASS::KEY_WORD
	};



	Tokenizer::Tokenizer()
	{
		N = 0;
		i = 0;
		prev = TOKEN_CLASS::NONE;
	}

    Tokenizer::~Tokenizer()
	{}

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

	unique_ptr<Token> Tokenizer::readOthers()
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
			throw CalcException("Unrecognized symbol '\\"+command[i], command, i);
		}
		prev = type;
		string temp = ""; 
		temp += command[i];
		return make_unique<Token>(temp, type,i++);
	}

	unique_ptr<Operator> Tokenizer::readOperator()
	{
		auto result = OperatorsFactory::get(command, i);
		if (result != nullptr)
		{
			prev = TOKEN_CLASS::OPERATOR;
			result->setPosition(i);
			i += result->getLexemeR().size();
		}
		return result;
	}

	unique_ptr<SNumber> Tokenizer::readNumber()
	{
		string out;
		NumberReader::read(command, out, i);
		i += out.size();
		prev = TOKEN_CLASS::NUMBER;
		return make_unique<SNumber>(Token(out, TOKEN_CLASS::NUMBER, i));
	}

	unique_ptr<Token> Tokenizer::readWord()
	{
		int start = i;
		string lexame="";
		while (i < N && (TokenizerHelper::isLetter(command[i]) || TokenizerHelper::isDigit(command[i])))
			lexame += command[i++];
		prev = TokenizerHelper::keyWordOrId(lexame);
		return make_unique<Token>(lexame,prev, start);
	}

	void Tokenizer::readString()
	{
		
	}

	unique_ptr<Token> Tokenizer::readWhiteSpace()
	{
		switch (command[i])
		{
		case '\n':
			prev = TOKEN_CLASS::NEW_LINE;
			return make_unique<Token>("\n", TOKEN_CLASS::NEW_LINE, i++);
		case '\t':
		case ' ':
		case '\r':
			prev = TOKEN_CLASS::SPACE;
			return make_unique<Token>(" ", TOKEN_CLASS::SPACE, i++);
		default:
			throw CalcException("d");
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

	bool Tokenizer::hasNext()
	{
		if (i < N)
		{
			if (i < N - 1 && command[i] == '/' && command[i + 1] == '*')
			{
				skipBlockComment();
				return hasNext();
			}
			else if (command[i] == '%' || (i < N - 1 && command[i] == '/'&&command[i + 1] == '/'))
			{
				skipLineComment();
				return hasNext();
			}
			else if ((command[i] == ' ' || command[i] == '\t' || command[i] == '\r') &&
				find(Tokenizer::FOR_SPACE_DELETE, prev))
			{
				i++;
				return hasNext();
			}
			else if ((command[i] == '\n' && (prev == TOKEN_CLASS::NEW_LINE || prev == TOKEN_CLASS::NONE || prev == TOKEN_CLASS::SEMICOLON)) ||
				(i < N - 1 && command[i]=='\n'&&command[i + 1] == ';'))
			{
				i++;
				return hasNext();
			}
		}

		return i < N;
	}

	void Tokenizer::deleteUneccessary()
	{
		
	}

	unique_ptr<Token> Tokenizer::getNext()
	{	
		if (TokenizerHelper::isDigit(command[i]))
			return readNumber();
		if (TokenizerHelper::isLetter(command[i]))
			return readWord();
		if (TokenizerHelper::isWhiteSpace(command[i]))
			return readWhiteSpace();
	
		auto op = readOperator();
		if (op != nullptr)
			return std::move(op);
		
		return readOthers();
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


}