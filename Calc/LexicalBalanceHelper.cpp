#include "stdafx.h"
#include "LexicalBalanceHelper.h"

namespace KLab
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
		pos = line = 1;
	}

	PARSE_MODE LexicalBalanceHelper::getMode()const
	{
		return mode.back();
	}

	void LexicalBalanceHelper::changeMode(PARSE_MODE modeA, bool start)
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
			if (mode.back() != modeA || balance.back() == 0)
			{
				throw CalcException("Expression or statement is incorrect--possibly unbalanced (, {,or[ or at least one END is missing!", "", pos, line);
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
		pos = token.getColumn();
		line = token.getLine();
		switch (token.getTokenClass())
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
		case TOKEN_CLASS::ELSEIF_KEYWORD:
			onElseIf(token);
			break;
		case TOKEN_CLASS::ELSE_KEYWORD:
			token.setKeywordBalance(key_word_balance);
			break;
		case TOKEN_CLASS::IF_KEYWORD:
		case TOKEN_CLASS::FOR_KEYWORD:
		case TOKEN_CLASS::WHILE_KEYWORD:
		case TOKEN_CLASS::FUNCTION_KEYWORD:
			onInstructionKeyWord(token);
			break;
		case TOKEN_CLASS::BREAK_KEYWORD:
		case TOKEN_CLASS::CONTINUE_KEYWORD:
			onContBreakKeyWords();
			break;
		}
		token.setMode(mode.back());
	}

	void LexicalBalanceHelper::onElseIf(Token &token)
	{
		if (key_word_balance == 0 || key_word_mode.back() != TOKEN_CLASS::IF_KEYWORD)
			throw CalcException("Unexpected 'elseif' outside 'if'", "", pos, line);
		token.setKeywordBalance(key_word_balance);
	}

	void LexicalBalanceHelper::onInstructionKeyWord(Token &token)
	{
		token.setKeywordBalance(++key_word_balance);
		key_word_mode.push_back(token.getTokenClass());
	}

	void LexicalBalanceHelper::onEndKeyword(Token &token)
	{
		if (key_word_balance == 0)
			throw CalcException("Unexpected end keyword!", "", pos, line);
		token.setKeywordBalance(key_word_balance--);

		switch (key_word_mode.back())
		{
		case TOKEN_CLASS::FOR_KEYWORD:
			token.setTokenClass(TOKEN_CLASS::END_FOR);
			break;
		case TOKEN_CLASS::IF_KEYWORD:
			token.setTokenClass(END_IF);
			break;
		case TOKEN_CLASS::WHILE_KEYWORD:
			token.setTokenClass(END_WHILE);
			break;
		case TOKEN_CLASS::FUNCTION_KEYWORD:
			token.setTokenClass(TOKEN_CLASS::END_FUNCTION);
			break;
		}
		key_word_mode.pop_back();
	}

	void LexicalBalanceHelper::onContBreakKeyWords()
	{
		if (key_word_balance == 0 || !find(key_word_mode, FOR_KEYWORD) && !find(key_word_mode, WHILE_KEYWORD))
			throw CalcException("Cannot use break or continue outside loop", "", pos, line);
	}

	void LexicalBalanceHelper::throwOnUnbalancedEnd()
	{
		if (key_word_balance || balance.size() > 1 || balance.back() != 0)
			throw CalcException("This statement is incomplete.", "", pos, line);
	}
}