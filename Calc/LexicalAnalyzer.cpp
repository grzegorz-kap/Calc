#include "stdafx.h"
#include "LexicalAnalyzer.h"


namespace PR
{
	const vector<TOKEN_CLASS> LexicalAnalyzer::UNARY_OP_PRECURSORS = 
	{
		TOKEN_CLASS::COMMA,
		TOKEN_CLASS::SEMICOLON,
		TOKEN_CLASS::COLON,
		TOKEN_CLASS::OPEN_PARENTHESIS,
		TOKEN_CLASS::MATRIX_START,
		TOKEN_CLASS::NONE,
		TOKEN_CLASS::KEY_WORD,
		TOKEN_CLASS::NEW_LINE
	};
	
	LexicalAnalyzer::LexicalAnalyzer()
	{
		reset();
	}

	LexicalAnalyzer::LexicalAnalyzer(const string &command)
		:LexicalAnalyzer()
	{
		setInput(command);
	}

	LexicalAnalyzer::~LexicalAnalyzer()
	{
	}

	void LexicalAnalyzer::reset()
	{
		prev = TOKEN_CLASS::NONE;
		what_next_flag = false;
	}

	void LexicalAnalyzer::setInput(const string &name)
	{
		tokenizer.setInput(name);
	}

	void LexicalAnalyzer::push( Token token)
	{
		balancer.setMode(token);

		switch (token.getClass())
		{
		case TOKEN_CLASS::SPACE: 
			onSpace(token); 
			break;
		case TOKEN_CLASS::OPERATOR: 
			onOperator(token); 
			break;
		}

		prev = token.getClass();
		q.push(token);
	}

	void LexicalAnalyzer::onComma(Token &token)
	{

	}

	void LexicalAnalyzer::onSpace(Token &token)
	{
		if (balancer.getMode() == PARSE_MODE::MATRIX)
			token.set_class(TOKEN_CLASS::COMMA);
	}

	void LexicalAnalyzer::onOperator(Token &token)
	{
		string name = token.getLexeme();
		
		if (name == "+" || name == "-")
		{
			if (find(LexicalAnalyzer::UNARY_OP_PRECURSORS, token.getClass()) ||
				(prev==TOKEN_CLASS::OPERATOR&&prev_operator_args_num > 1))
			{
				token.setLexeme("$" + name);
				token.setParam(Operator::find(name));
			}
		}

		prev_operator_args_num = Operator::OPERATORS[token.getParam()].getArguments();
		
	}

	bool LexicalAnalyzer::hasNext()
	{
		if (q.size() > 1 || q.size() == 1 && !tokenizer.hasNext())
			return true;
	
		if (tokenizer.hasNext())
		{
			read();
			return true;
		}
		else
			return false;
	}

	void LexicalAnalyzer::read()
	{
		Token current = tokenizer.getNext();
		if (current.getClass() == TOKEN_CLASS::SPACE)
		{
			Token next = tokenizer.hasNext() ? tokenizer.getNext() : Token(TOKEN_CLASS::NONE);
			if (find<TOKEN_CLASS>(Tokenizer::FOR_SPACE_DELETE, next.getClass()))
			{
				push(next);
			}
			else
			{
				push(current);
				push(next);
			}
		}
		else
			push(current);
	}

	Token LexicalAnalyzer::getNext()
	{
		Token t = q.front();
		q.pop();
		what_next_flag = false;
		return t;
	}

	TOKEN_CLASS LexicalAnalyzer::whatNext()
	{
		if (!hasNext())
			return TOKEN_CLASS::NONE;
		else
		{
			if (!what_next_flag)
				read();
			what_next_flag = true;
			return q.front().getClass();
		}
	}
}
