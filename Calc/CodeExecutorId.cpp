#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	void CodeExecutor::onID()
	{
		auto result = vars_ref.find((*i)->getLexemeR());
		
		if (result == vars_ref.end())
			throw CalcException("Undefined function or variable '" + (*i)->getLexemeR() + "'.",(*i)->getPosition());

		stack.push_back(result->second);
	}
}