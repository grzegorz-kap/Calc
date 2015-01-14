 #include "stdafx.h"
#include "Tokenizer.h"

namespace PR
{
	const vector<TOKEN_CLASS> Tokenizer::FOR_SPACE_DELETE = {
		TOKEN_CLASS::NEW_LINE,  TOKEN_CLASS::OPEN_PARENTHESIS,
		TOKEN_CLASS::CLOSE_PARENTHESIS, TOKEN_CLASS::SPACE, TOKEN_CLASS::COLON,
		TOKEN_CLASS::SEMICOLON, TOKEN_CLASS::COMMA, TOKEN_CLASS::IF_KEYWORD, FOR_KEYWORD,
		TOKEN_CLASS::WHILE_KEYWORD, TOKEN_CLASS::CONTINUE_KEYWORD, TOKEN_CLASS::BREAK_KEYWORD, TOKEN_CLASS::END_KEYWORD,
		TOKEN_CLASS::FUNCTION_KEYWORD,TOKEN_CLASS::ELSEIF_KEYWORD,TOKEN_CLASS::RETURN_KEYWORD
	};

	const vector<string> Tokenizer::END_SYNONIMS = {
		"endfor", "endif", "endwhile", "endfunction"
	};

	const unordered_map<char, TOKEN_CLASS> Tokenizer::OTHERS = {
		{ '(',TOKEN_CLASS::OPEN_PARENTHESIS},
		{ ')',TOKEN_CLASS::CLOSE_PARENTHESIS },
		{ '[',TOKEN_CLASS::MATRIX_START },
		{ ']',TOKEN_CLASS::MATRIX_END },
		{ ':',TOKEN_CLASS::COLON },
		{ ';',TOKEN_CLASS::SEMICOLON },
		{ ',',TOKEN_CLASS::COMMA }
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
		auto result = OTHERS.find(command[i]);
		if (result == OTHERS.end())
			throwMessage("Unrecognized symbol");
		tokens.push_back(make_unique<Token>( result->second));
		setLine();
		inc();
	}

	bool Tokenizer::readOperator()
	{
		if (command[i] == '\'' && prevChar() != '.' && !find(TokenizerHelper::NO_STRING_PRECURSORS, prev()))
		{
			readString();
			return true;
		}

		int length;
		auto result = OperatorsFactory::get(command, i,length);
		if (result != nullptr)
		{
			tokens.push_back(std::move(result));
			setLine();
			inc(length);
			return true;
		}
		return false;
	}

	void Tokenizer::readNumber()
	{
		try{
			tokens.push_back(make_unique<SNumber>(Token(NumberReader::read(command, i), TOKEN_CLASS::NUMBER)));
			setLine();
			inc(tokens.back()->getLexemeR().size());
		}
		catch (const CalcException &ex)
		{
			throwMessage(ex.getMessageR());
		}
	}

	void Tokenizer::readWord()
	{
		
		string lexame="";
		/* Wczytanie identyfikatora*/
		while (i < N && 
				(  TokenizerHelper::isLetter(command[i]) || 
				   TokenizerHelper::isDigit(command[i])  ) 
				)
			lexame += command[i++];

		/* Zamiana endfor, endif, endwhile, endfunction na end. */
		if (std::find(END_SYNONIMS.cbegin(), END_SYNONIMS.cend(), lexame) 
			!= END_SYNONIMS.end())
			lexame = "end";

		/* Dodanie do tablicy rozpoznanych symboli leksykalnych. */
		tokens.push_back(make_unique<Token>(std::move(lexame),
						TokenizerHelper::keyWordOrId(lexame)));
		setLine();
		_position += tokens.back()->getLexemeR().size();
	}

	void Tokenizer::readString()
	{
		string lexame = "";
		bool found = false;
		i++;
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
			throwMessage("A KapiLab string constant is not terminated properly.");
		tokens.push_back(make_unique<String>(std::move(lexame)));
		setLine();
		_position += tokens.back()->getLexemeR().size();
	}

	void Tokenizer::readWhiteSpace()
	{
		switch (command[i])
		{
		case '\n':
			tokens.push_back(make_unique<Token>("\n", TOKEN_CLASS::NEW_LINE));
			setLine();
			i++;
			onNewLine();
			break;
		case '\t':
		case ' ':
		case '\r':
			if (tokens.size() != 0 && !find(FOR_SPACE_DELETE, tokens.back()->getClass()))
			{
				tokens.push_back(make_unique<Token>(TOKEN_CLASS::SPACE));
				setLine();
			}
			inc();
			break;
		}
	}

	void Tokenizer::skipBlockComment()
	{
		while (i < N - 1)
		{
			if (command[i] == '%'&&command[i + 1] == '}')
				break;
			else if (command[i] == '\n')
				onNewLine();
			inc();
		}
		inc(2);
	}

	void Tokenizer::skipLineComment()
	{
		while (i < N &&command[i++] != '\n')
			_position++;
		i--;
	}

	void Tokenizer::deleteUneccessary()
	{
		if (i < N)
		{
			char z = command[i];
			if (i < N - 1 && z == '%' && command[i + 1] == '{')
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
				onNewLine();
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
			else if (onDot())
				continue;
			else if (readOperator())
				continue;
			else readOthers();
			deleteUneccessary();
		}
	}

	bool Tokenizer::onDot()
	{
		if (i < N - 2 && command[i] == '.'&& command[i + 1] == '.' && command[i + 2] == '.')
		{
			inc(3);
			while (i < N && command[i] != '\n')
				inc();
			i++;
			onNewLine();
		}
		else
			return false;
		return true;
	}

	void Tokenizer::whiteSpacesBegin()
	{
		while (i < N&&TokenizerHelper::isWhiteSpace(command[i]))
		{
			i++;
			if (command[i] == '\n')
				onNewLine();
			else
				_position++;
		}
				
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
		_line = 1;
		_position = 1;
		whiteSpacesEnd();
		whiteSpacesBegin();
		
	}

	char Tokenizer::prevChar()
	{
		if (i == 0)
			return 0;
		return command[i - 1];
	}

	void Tokenizer::throwMessage(const string &message)
	{
		throw CalcException(message, "", _position, _line);
	}

	void Tokenizer::inc(int val)
	{
		i += val;
		_position += val;
	}

	void Tokenizer::onNewLine()
	{
		_position = 1;
		_line++;
	}

	void Tokenizer::setLine()
	{
		if (tokens.size())
		{
			tokens.back()->setLine(_line);
			tokens.back()->setPosition(_position);
		}
			
	}
}