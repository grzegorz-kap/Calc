#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	bool CodeExecutor::checkWhile()
	{
		if (isKeyword(TOKEN_CLASS::WHILE_KEYWORD))
		{
			onWHILE();
			return true;
		}
		if (isKeyword(TOKEN_CLASS::END_WHILE))
		{
			onWhileEnd();
			return true;
		}
		return false;
	}

	void CodeExecutor::onWhileEnd()
	{
		ip = code.get(conditions.back());
		assignment_flag = true;
		output_off_flag = true;
		if (*run() == false)
		{
			conditions.pop_back();
			code.inc();
		}
		else
		{
			code.setIp(conditions.back() + 1);
		}
	}

	void CodeExecutor::onWHILE()
	{
		int balance = ip->at(0)->getKeywordBalance();
		next();
		conditions.push_back(code.getLP());
		assignment_flag = true;
		output_off_flag = true;
		if (*run() == false)
		{
			next();
			setIPTo(WHILE_FIND, balance);
		}
		code.inc();
	}
}