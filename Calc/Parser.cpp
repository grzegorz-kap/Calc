#include "stdafx.h"
#include "Parser.h"



namespace PR
{
	Parser::Parser(LexicalAnalyzer &lex)
		:
		lexAnalyzer(lex)
	{
		stop = false;
	}

	Parser::~Parser()
	{
		
	}

	void Parser::onComma()
	{
		if (i->getMode() == PARSE_MODE::NORMAL||i->getMode()==PARSE_MODE::KEYWORD)
			stop = true;
		else
		{
			TOKEN_CLASS type = i->getMode() == PARSE_MODE::FUNCTION ? TOKEN_CLASS::OPEN_PARENTHESIS : TOKEN_CLASS::MATRIX_START;
			bool flag = false;
			for (int i = stack.size()-1; i >= 0; i--)
			{
				if (stack[i]->getClass() == type)
				{
					flag = true;
					break;
				}
				else
					stackToOnp();
			}
			if (!flag)
				throw CalcException("Unbalanced parenthesis!");
		}
	}

	void Parser::onFunction()
	{
		onp.push_back(make_unique<Token>(TOKEN_CLASS::FUNCTON_ARGS_END));
		stack.push_back(make_unique<Token>(*i));
	}

	void Parser::onID()
	{
		
		if (lexAnalyzer.whatNext() == TOKEN_CLASS::OPEN_PARENTHESIS)
		{
			Token token = *i;
			token.set_class(TOKEN_CLASS::FUNCTION);
			stack.push_back(make_unique<Token>(token));
			onp.push_back(make_unique<Token>(TOKEN_CLASS::FUNCTON_ARGS_END));
		}
		else
			onp.push_back(make_unique<Token>(*i));
	}

	void Parser::onNewLine()
	{
		if (i->getMode() == PARSE_MODE::MATRIX)
			onSemicolon();
		else if (onp.size())
			stop = true;
	}

	void Parser::onNumber()
	{
		onp.push_back(std::move(i));
	}

	void Parser::stackToOnpUntilToken(TOKEN_CLASS type,bool remove)
	{
		bool flag = true;
		for (int i = stack.size() - 1; i >= 0; i--)
		{
			if (stack[i]->getClass() == type)
			{
				flag = false;
				if (remove)
					stack.pop_back();
				break;
			}
			else
				stackToOnp();
		}
		if (flag)
			throw CalcException("Unbalanced or unexpected parenthesis or bracket.");
	}

	void Parser::onOpenParenthesis()
	{
		stack.push_back(make_unique<Token>(*i));
	}

	void Parser::onCloseParenthesis()
	{
		stackToOnpUntilToken(TOKEN_CLASS::OPEN_PARENTHESIS);
		if (stackBack() == TOKEN_CLASS::FUNCTION )
			stackToOnp();
	}

	void Parser::onOperator()
	{
		while (stackBack() == TOKEN_CLASS::OPERATOR &&
			i->castToOperator() < stack.back()->castToOperator())
			stackToOnp();
		stack.push_back(std::move(i));
	}

	void Parser::onMatrixStart()
	{
		stack.push_back(make_unique<Token>(*i));
		onp.push_back(make_unique<Token>(*i));
	}

	void Parser::onMatrixEnd()
	{
		stackToOnpUntilToken(TOKEN_CLASS::MATRIX_START);
		if (i->getMode()!=PARSE_MODE::MATRIX)
			onp.push_back(make_unique<Token>(TOKEN_CLASS::VERSE_END));
		onp.push_back(make_unique<Token>(*i));
	}

	bool Parser::onColon()
	{
		if (lexAnalyzer.whatNext() == TOKEN_CLASS::CLOSE_PARENTHESIS || lexAnalyzer.whatNext() == TOKEN_CLASS::COMMA)
		{
			onp.push_back(make_unique<Token>(":",TOKEN_CLASS::MATRIX_ALL,i->getPosition()));
			return true;
		}
		else
			return false;
	}

	void Parser::onSemicolon()
	{
		switch (i->getMode())
		{
		case PARSE_MODE::MATRIX:
			stackToOnpUntilToken(TOKEN_CLASS::MATRIX_START,false);
			onp.push_back(make_unique<Token>(TOKEN_CLASS::VERSE_END));
			break;
		case PARSE_MODE::NORMAL:
		case PARSE_MODE::KEYWORD:
			stop = true;
			stackToOnpAll();
			onp.push_back(make_unique<Token>(";", TOKEN_CLASS::OUTPUT_OFF, i->getPosition()));
			break;
		}
	}

	bool Parser::parse()
	{
		stack.clear();
		onp.clear();
		stop = false;

		while (!stop&&lexAnalyzer.hasNext())
		{
			i = lexAnalyzer.getNext();
			switch (i->getClass())
			{
			case TOKEN_CLASS::NUMBER: 
				onNumber(); 
				break;
			case TOKEN_CLASS::ID:
				onID();
				break;
			case TOKEN_CLASS::COMMA:
				onComma();
				break;
			case TOKEN_CLASS::OPEN_PARENTHESIS:
				onOpenParenthesis();
				break;
			case TOKEN_CLASS::FUNCTION:
				onFunction();
				break;
			case TOKEN_CLASS::SEMICOLON:
				onSemicolon();
				break;
			case TOKEN_CLASS::OPERATOR:
				if (i->getLexeme() == ":"&&onColon())
					break;
				onOperator();
				break;
			case TOKEN_CLASS::CLOSE_PARENTHESIS:
				onCloseParenthesis();
				break;
			case TOKEN_CLASS::NEW_LINE:
				onNewLine();
				break;
			case TOKEN_CLASS::MATRIX_START:
				onMatrixStart();
				break;
			case TOKEN_CLASS::MATRIX_END:
				onMatrixEnd();
				break;
			case TOKEN_CLASS::KEY_WORD:
				if (onp.size() == 0 && stack.size() == 0)
					onp.push_back(make_unique<Token>(*i));
				stop = true;
				break;
			default:
				throw "Exception parsing!";
				break;
			}
		}

		stackToOnpAll();
		
		if (lexAnalyzer.hasNext())
			return true;
		else
			return false;
	}

	TOKEN_CLASS Parser::stackBack() const
	{
		if (stack.size() != 0)
			return stack.back()->getClass();
		else
			return TOKEN_CLASS::NONE;
	}

	TOKEN_CLASS Parser::onpBack() const
	{
		if (onp.size() != 0)
			return onp.back()->getClass();
		else
			return TOKEN_CLASS::NONE;
	}

	void Parser::stackToOnpAll()
	{
		for (int i = stack.size() - 1; i >= 0; i--)
		{
			if (stack[i]->getClass() != TOKEN_CLASS::OPERATOR)
				throw CalcException("Unexpected symbol!", stack[i]->getPosition());
			onp.push_back(std::move(stack[i]));
		}
		stack.clear();
	}
	
	void Parser::stackToOnp()
	{
		onp.push_back(std::move(stack.back()));
		stack.pop_back();
	}
}