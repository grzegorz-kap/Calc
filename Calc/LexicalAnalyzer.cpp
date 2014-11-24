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

	void LexicalAnalyzer::setInput(const string &name)
	{
		tokenizer.setInput(name);
	}

	void LexicalAnalyzer::setInput(string &&name)
	{
		tokenizer.setInput(std::move(name));
	}

	void LexicalAnalyzer::setInput(FileLoader &file)
	{
		tokenizer.setInput(file.loadAll());
	}

	void LexicalAnalyzer::reset()
	{
		prev = TOKEN_CLASS::NONE;
	}

	auto LexicalAnalyzer::getTokens()
		-> decltype(tokens)
	{
		tokenizer.tokenize();
		tokens = tokenizer.getTokens();

		prev = TOKEN_CLASS::NONE;
		for (iter = tokens.begin(); iter != tokens.end(); )
		{
			process(*iter);
			if (for_delete)
			{
				iter = tokens.erase(iter);
				continue;
			}
			iter++;
		}

		balancer.throwOnUnbalancedEnd();
		return std::move(tokens);
	}

	void LexicalAnalyzer::onEndKeyword(Token &token)
	{
		if (balancer.getMode() != PARSE_MODE::FUNCTION)
			return;
		token.set_class(LAST_INDEX_OF);
	}

	void LexicalAnalyzer::process(unique_ptr<Token> & token)
	{
		for_delete = false;
		
		if (token->getClass() == END_KEYWORD)
			onEndKeyword(*token);

		balancer.setMode(*token);
		switch (token->getClass())
		{
		case TOKEN_CLASS::SPACE: 
			onSpace(*token); 
			break;
		case TOKEN_CLASS::OPERATOR: 
			onOperator(token); 
			break;
		case TOKEN_CLASS::COLON:
			onColon(*token);
			break;
		}
		
		if (!for_delete)
			prev = token->getClass();
	}

	void LexicalAnalyzer::onColon(Token &token)
	{
		if (token.getMode() == PARSE_MODE::FUNCTION)
		{
			if (prev == TOKEN_CLASS::OPEN_PARENTHESIS || prev == TOKEN_CLASS::COMMA ||
				whatNext() == TOKEN_CLASS::CLOSE_PARENTHESIS || whatNext() == TOKEN_CLASS::COMMA)
				token.set_class(TOKEN_CLASS::MATRIX_ALL);
		}
	}

	void LexicalAnalyzer::onComma(Token &token)
	{

	}

	void LexicalAnalyzer::onSpace(Token &token)
	{
		if (balancer.getMode() == PARSE_MODE::MATRIX)
			token.set_class(TOKEN_CLASS::COMMA);
		else
			if (find(Tokenizer::FOR_SPACE_DELETE, whatNext()))
				for_delete = true;
	}

	void LexicalAnalyzer::onOperator(unique_ptr<Token> &token)
	{
		string name = token->getLexemeR();
		if (name == "+" || name == "-")
		{
			if (find(LexicalAnalyzer::UNARY_OP_PRECURSORS, prev) ||
				(prev==TOKEN_CLASS::OPERATOR&&(prev_operator_args_num > 1||ev_op_prev==EVAULATED::LEFT)))
			{
				token = OperatorsFactory::simple_get("$" + name);
				
				if (prev == TOKEN_CLASS::OPERATOR)
				{
					const string &prevlexeme = (iter - 1)->get()->getLexemeR();
					if (prevlexeme == "^" || prevlexeme == ".^")
						token->castToOperator()->setPriority(19);
				}
			}
		}

		if (name == "~" && prev==TOKEN_CLASS::OPERATOR)
		{
			const string &prevlexeme = (iter - 1)->get()->getLexemeR();
			if (prevlexeme == "^" || prevlexeme == ".^")
				token->castToOperator()->setPriority(19);
		}

		prev_operator_args_num = token->castToOperator()->getArgumentsNum();
		ev_op_prev = token->castToOperator()->getEv();
	}

	TOKEN_CLASS LexicalAnalyzer::whatNext()
	{
		if (iter + 1 == tokens.end())
			return TOKEN_CLASS::NONE;
		return (*(iter+1))->getClass();
	}
}
