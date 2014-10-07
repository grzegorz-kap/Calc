#include "stdafx.h"
#include "Tokenizer.h"
#include "CalcException.h"



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

	void Tokenizer::setInput(const string &command)
	{
		this->command = command;
		N = command.size();
		i = 0;
		whiteSpacesEnd();
		whiteSpacesBegin();
	}

	Token Tokenizer::readOthers()
	{
		TOKEN_CLASS type;
	//	auto temp2 = command[i];
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
		string temp = ""; temp += command[i];
		return Token(temp, type,i++);
	}

	bool Tokenizer::readOperator(Token &t)
	{
		int N = Operator::OPERATORS.size();
		for (int i = 0; i < N;i++)
		{
			if (command.compare(this->i, Operator::OPERATORS[i].getLexemeR().size(), Operator::OPERATORS[i].getLexemeR()) == 0)
			{
				Operator op = Operator::OPERATORS[i];
				t= Token(op.getLexemeR(), TOKEN_CLASS::OPERATOR, this->i,i);
				this->i += op.getLexemeR().size();
				prev = TOKEN_CLASS::OPERATOR;
				return true;
			}
		}
		return false;
	}

	Token Tokenizer::readNumber()
	{
		string out;
		NumberReader::read(command, out, i);
		i += out.size();
		prev = TOKEN_CLASS::NUMBER;
		return Token(out, TOKEN_CLASS::NUMBER, i);
	}

	Token Tokenizer::readWord()
	{
		int start = i;
		string lexame="";
		while (i < N && (TokenizerHelper::isLetter(command[i]) || TokenizerHelper::isDigit(command[i])))
			lexame += command[i++];
		prev = TokenizerHelper::keyWordOrId(lexame);
		return Token(lexame,prev, start);
	}

	void Tokenizer::readString()
	{
		
	}

	Token Tokenizer::readWhiteSpace()
	{
		switch (command[i])
		{
		case '\n':
			prev = TOKEN_CLASS::NEW_LINE;
			return Token("\n", TOKEN_CLASS::NEW_LINE, i++);
		case '\t':
		case ' ':
		case '\r':
			prev = TOKEN_CLASS::SPACE;
			return Token(" ", TOKEN_CLASS::SPACE, i++);
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

	Token Tokenizer::getNext()
	{	
		if (TokenizerHelper::isDigit(command[i]))
			return readNumber();
		if (TokenizerHelper::isLetter(command[i]))
			return readWord();
		if (TokenizerHelper::isWhiteSpace(command[i]))
			return readWhiteSpace();
		Token t;
		if (readOperator(t))
			return t;
		else 
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