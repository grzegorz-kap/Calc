#include "stdafx.h"
#include "Parser.h"



namespace PR
{
	Parser::Parser()
	{

	}

	Parser::Parser(LexicalAnalyzer &lex)
	{
		tokens = lex.getTokens();
		iter = tokens.begin();
	}

	Parser::~Parser()
	{
		
	}

	void Parser::setInput(LexicalAnalyzer &lex)
	{
		tokens = lex.getTokens();
		iter = tokens.begin();
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
		onp.push_back(make_shared<Token>(TOKEN_CLASS::FUNCTON_ARGS_END));
		stack.push_back(make_shared<Token>(*i));
	}

	void Parser::onID()
	{		
		if (whatNext() == TOKEN_CLASS::OPEN_PARENTHESIS)
		{
			Token token = *i;
			token.set_class(TOKEN_CLASS::FUNCTION);
			stack.push_back(make_shared<Token>(token));
			onp.push_back(make_shared<Token>(TOKEN_CLASS::FUNCTON_ARGS_END));

			if (token.getLexemeR() == "mpf_float")
			{
				_ev_type_mode.push_back(TYPE::R_DOUBLE);
				_ev_type_balance.push_back(0);
			}
			else if (token.getLexemeR() == "double")
			{
				_ev_type_balance.push_back(0);
				_ev_type_mode.push_back(TYPE::DOUBLE);
			}
		}
		else
			onp.push_back(make_shared<Token>(*i));
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
		if (_ev_type_mode.size())
			i->setEvType(_ev_type_mode.back());
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
		if (_ev_type_balance.size())
			_ev_type_balance.back()++;

		stack.push_back(make_unique<Token>(*i));
	}

	void Parser::onCloseParenthesis()
	{
		if (_ev_type_balance.size() && _ev_type_balance.back()-- == 1)
		{
			_ev_type_balance.pop_back();
			_ev_type_mode.pop_back();
		}

		stackToOnpUntilToken(TOKEN_CLASS::OPEN_PARENTHESIS);
		if (stackBack() == TOKEN_CLASS::FUNCTION )
			stackToOnp();
	}

	void Parser::onOperator()
	{ 
		Operator *o1 = i->castToOperator();
		while (stackBack() == TOKEN_CLASS::OPERATOR)
		{
			Operator *o2 = stack.back()->castToOperator();
			if (o1->getLexemeR() == ":" && o2->getLexemeR() == ":")
			{
				stack.pop_back();
				stack.push_back(make_unique<Colon3Operator>());
				return;
			}
			if (*o1 < *o2)
				stackToOnp();
			else
				break;
		}
		stack.push_back(std::move(i));
	}

	void Parser::onMatrixStart()
	{
		stack.push_back(make_unique<Token>(*i));
		onp.push_back(make_unique<Token>(*i));
		if (_ev_type_mode.size())
			onp.back()->setEvType(_ev_type_mode.back());
	}

	void Parser::onMatrixAll()
	{
		stack.push_back(make_unique<Token>(*i));
	}

	void Parser::onMatrixEnd()
	{
		stackToOnpUntilToken(TOKEN_CLASS::MATRIX_START);
		if (i->getMode()!=PARSE_MODE::MATRIX)
			onp.push_back(make_unique<Token>(TOKEN_CLASS::VERSE_END));
		onp.push_back(make_unique<Token>(*i));
	}

	void Parser::onColon()
	{
		i = make_unique<Colon2Operator>();
		onOperator();
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
			onp.push_back(make_shared<Token>(TOKEN_CLASS::OUTPUT_OFF));
			break;
		}
	}

	bool Parser::parse()
	{
		stack.clear();
		onp.clear();
		stop = false;

		for (;!stop && iter!= tokens.end();++iter)
		{
			i = std::move(*iter);
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
			case TOKEN_CLASS::COLON:
				onColon();
				break;
			case TOKEN_CLASS::MATRIX_ALL:
				onMatrixAll();
				break;
			case TOKEN_CLASS::FOR_KEYWORD:
				onKeywordFOR();
				stop = true;
				break;
			case TOKEN_CLASS::KEY_WORD:
			case TOKEN_CLASS::IF_KEYWORD:
			case TOKEN_CLASS::ELSE_KEYWORD:
			case TOKEN_CLASS::END_IF:
			case TOKEN_CLASS::END_WHILE:
			case TOKEN_CLASS::WHILE_KEYWORD:
			case TOKEN_CLASS::FUNCTION_KEYWORD:
			case TOKEN_CLASS::END_FUNCTION:
			case TOKEN_CLASS::END_FOR:
				if (onp.size() == 0 && stack.size() == 0)
					onp.push_back(make_unique<Token>(*i));
				stop = true;
				break;
			default:
				throw CalcException("Unexpected symbol: '" + i->getLexemeR() + "'.", i->getPosition());
				break;
			}
		}

		stackToOnpAll();
		changeIfAssignment();
		return iter != tokens.end();
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

	void Parser::iterBack()
	{
		if (tokens.begin() != iter)
			iter--;
	}
}