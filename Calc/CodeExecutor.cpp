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

	unique_ptr<Data> CodeExecutor::run(const Instruction &tokens)
	{
		for (i = tokens.begin(); i != tokens.end(); i++)
		{
			switch ((*i)->getClass())
			{
			case TOKEN_CLASS::NUMBER:
				stack.push_back(unique_ptr<Data>((*i)->evaluate()));
				break;
			case TOKEN_CLASS::OPERATOR:
				onOperator();
				break;
			}
		}
		return unique_ptr<Data>(new Data());
	}

	void CodeExecutor::onOperator()
	{
		auto p = dynamic_cast<Operator *>(i->get());
		p->setArguments(stack);
 		stack.push_back(unique_ptr<Data>(p->evaluate()));
	}
	
}
