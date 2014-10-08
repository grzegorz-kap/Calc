#include "stdafx.h"
#include "CodeExecutor.h"


namespace PR
{

	CodeExecutor::CodeExecutor()
	{
	}


	CodeExecutor::~CodeExecutor()
	{
	}

	shared_ptr<Data> CodeExecutor::run(const Instruction &tokens)
	{
		for (i = tokens.begin(); i != tokens.end(); i++)
		{
			
		}
		return shared_ptr<Data>(new Data());
	}
	
}
