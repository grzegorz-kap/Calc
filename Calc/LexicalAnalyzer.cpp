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

	void LexicalAnalyzer::push(unique_ptr<Token> & token)
	{
		balancer.setMode(*token);

		switch (token->getClass())
		{
		case TOKEN_CLASS::SPACE: 
			onSpace(*token); 
			break;
		case TOKEN_CLASS::OPERATOR: 
			onOperator(token); 
			break;
		}
		prev = token->getClass();
		q.push(std::move(token));
	}

	void LexicalAnalyzer::onComma(Token &token)
	{

	}

	void LexicalAnalyzer::onSpace(Token &token)
	{
		if (balancer.getMode() == PARSE_MODE::MATRIX)
			token.set_class(TOKEN_CLASS::COMMA);
	}

	void LexicalAnalyzer::onOperator(unique_ptr<Token> &token)
	{
		const string & name = token->getLexemeR();
		if (name == "+" || name == "-")
		{
			if (find(LexicalAnalyzer::UNARY_OP_PRECURSORS, token->getClass()) ||
				(prev==TOKEN_CLASS::OPERATOR&&prev_operator_args_num > 1))
			{
				token = OperatorsFactory::simple_get("$" + name);
			}
		}
		prev_operator_args_num = token->castToOperator()->getArgumentsNum();
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
		unique_ptr<Token> current = tokenizer.getNext();
		if (current->getClass() == TOKEN_CLASS::SPACE)
		{
			unique_ptr<Token> next = tokenizer.hasNext() ? tokenizer.getNext() : make_unique<Token>(TOKEN_CLASS::NONE);
			if (find<TOKEN_CLASS>(Tokenizer::FOR_SPACE_DELETE, next->getClass()))
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

	unique_ptr<Token> LexicalAnalyzer::getNext()
	{
		unique_ptr<Token> t = std::move(q.front());
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
			return q.front()->getClass();
		}
	}
}
