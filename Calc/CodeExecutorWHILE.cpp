#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	bool CodeExecutor::checkWhile()
	{
		if (isKeyword(TOKEN_CLASS::WHILE_KEYWORD))
		{
			int balance = ip->at(0)->getKeywordBalance();
			next();
			if (*run() == false)
			{
				next();
				setIPTo(WHILE_FIND, balance);
			}
			code.inc();
			return true;
		}
		return false;
	}
}