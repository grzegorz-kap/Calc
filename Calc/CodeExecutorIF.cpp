#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	bool CodeExecutor::checkIF()
	{
		if (isKeyword(TOKEN_CLASS::IF_KEYWORD))
		{
			onIF();
			return true;
		}

		if (isKeyword(TOKEN_CLASS::END_IF))
		{
			code.inc();
			return true;
		}

		if (isKeyword(TOKEN_CLASS::ELSE_KEYWORD))
		{
			setIPTo(ELSE_FIND, ip->at(0)->getKeywordBalance());
			code.inc();
			return true;
		}

		return false;
	}

	void CodeExecutor::onIF()
	{
		int balance = ip->at(0)->getKeywordBalance();
		next();
		assignment_flag = true;
		output_off_flag = true;
		if (*run() == false)
		{
			next();
			setIPTo(IF_FIND, balance);
		}
		code.inc();
	}
}