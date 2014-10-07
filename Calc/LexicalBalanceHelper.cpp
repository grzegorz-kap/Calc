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
		switch (token.getType())
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
		case TOKEN_CLASS::KEY_WORD:
			string temp = token.getLexeme();
			if (temp == "end")
				changeMode(PARSE_MODE::KEYWORD, 0);
			else if (temp != "continue"&&temp != "break")
				changeMode(PARSE_MODE::KEYWORD, 1);
			break;
		}
		token.setMode(mode.back());
	}
}
