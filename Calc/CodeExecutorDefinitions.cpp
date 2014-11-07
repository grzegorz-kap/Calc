#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	const vector<TOKEN_CLASS> CodeExecutor::IF_FIND = 
	{ 
		TOKEN_CLASS::END_IF, 
		TOKEN_CLASS::ELSE_KEYWORD 
	};

	const vector<TOKEN_CLASS> CodeExecutor::ELSE_FIND = 
	{ 
		TOKEN_CLASS::END_IF 
	};

	const vector<TOKEN_CLASS> CodeExecutor::WHILE_FIND = 
	{ 
		TOKEN_CLASS::END_WHILE 
	};

	const vector<TOKEN_CLASS> CodeExecutor::FOR_FIND =
	{
		TOKEN_CLASS::END_FOR
	};
}