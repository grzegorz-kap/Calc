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
			switch ((*i)->getClass())
			{
			case TOKEN_CLASS::NUMBER:
				stack.push_back(unique_ptr<Data>((*i)->eveluate()));
				break;
			}
		}
		return shared_ptr<Data>(new Data());
	}
	
}
