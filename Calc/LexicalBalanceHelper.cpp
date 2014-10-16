#include "stdafx.h"
#include "LexicalBalanceHelper.h"

namespace PR
{

	LexicalBalanceHelper::LexicalBalanceHelper()
	{ 
		reset();
	}


	LexicalBalanceHelper::~LexicalBalanceHelper()
	{
	}

	void LexicalBalanceHelper::reset()
	{
		balance.push_back(0);
		mode.push_back(PARSE_MODE::NORMAL);
		key_word_balance = 0;
	}

	void LexicalBalanceHelper::changeMode(PARSE_MODE modeA,bool start)
	{
		if (start)
		{
			if (mode.back() != modeA)
			{
				mode.push_back(modeA);
				balance.push_back(1);
			}
			else
				balance.back()++;
		}
		else
		{
			if (mode.back() != modeA||balance.back()==0)
			{
				throw CalcException("Expression or statement is incorrect--possibly unbalanced (, {,or[ or at least one END is missing!",pos);
			}
			else
			{
				if (--balance.back() == 0)
				{
					balance.pop_back();
					mode.pop_back();
				}
			}
		}
	}

	void LexicalBalanceHelper::setMode(Token &token)
	{
		pos = token.getPosition();
		switch (token.getClass())
		{
		case TOKEN_CLASS::OPEN_PARENTHESIS:
			changeMode(PARSE_MODE::FUNCTION, 1);
			break;
		case TOKEN_CLASS::CLOSE_PARENTHESIS:
			changeMode(PARSE_MODE::FUNCTION, 0);
			break;
		case TOKEN_CLASS::MATRIX_START:
			changeMode(PARSE_MODE::MATRIX, 1);
			break;
		case TOKEN_CLASS::MATRIX_END:
			changeMode(PARSE_MODE::MATRIX, 0);
			break;
		case TOKEN_CLASS::END_KEYWORD:
			onEndKeyword(token);
			break;
		case TOKEN_CLASS::ELSE_KEYWORD:
			token.setKeywordBalance(key_word_balance);
			break;
		case TOKEN_CLASS::IF_KEYWORD:
		case TOKEN_CLASS::FOR_KEYWORD:
		case TOKEN_CLASS::WHILE_KEYWORD:
			onInstructionKeyWord(token);
			break;
		case TOKEN_CLASS::BREAK_KEYWORD:
		case TOKEN_CLASS::CONTINUE_KEYWORD:
			onContBreakKeyWords();
			break;
		}
		token.setMode(mode.back());
	}

	void LexicalBalanceHelper::onInstructionKeyWord(Token &token)
	{
		token.setKeywordBalance(++key_word_balance);
		key_word_mode.push_back(token.getClass());
	}

	void LexicalBalanceHelper::onEndKeyword(Token &token)
	{
		if (key_word_balance == 0)
			throw CalcException("Unexpected end keyword!");
		token.setKeywordBalance(key_word_balance--);
		
		switch (key_word_mode.back())
		{
		case TOKEN_CLASS::FOR_KEYWORD:
			token.set_class(TOKEN_CLASS::END_FOR);
			break;
		case TOKEN_CLASS::IF_KEYWORD:
			token.set_class(END_IF);
			break;
		case TOKEN_CLASS::WHILE_KEYWORD:
			token.set_class(END_WHILE);
			break;
		}
		key_word_mode.pop_back();
	}

	void LexicalBalanceHelper::onContBreakKeyWords()
	{
		if (key_word_balance == 0 || key_word_mode.back() != TOKEN_CLASS::FOR_KEYWORD && key_word_mode.back() != TOKEN_CLASS::WHILE_KEYWORD)
			throw CalcException("Cannot use break or continue outside loop");
	}
}
