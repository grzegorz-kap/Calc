#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	void CodeExecutor::onID()
	{
		auto result = vars_ref.find((*i)->getLexemeR());
		
		if (result != vars_ref.end())
			stack.push_back(result->second);
		else 
			if (!onScript())
				throw CalcException("Undefined variable or script '" + (*i)->getLexemeR() + "'.", (*i)->getPosition());
	}

	bool CodeExecutor::onScript()
	{
		if (ip->size() > 1)
			return false;

		FileLoader file((*i)->getLexeme() + ".m");
		if (!file.is_open())
			return false;

		CodeExecutor exec(vars_ref);
		exec.setInput(file);
		exec.start();
		assignment_flag = true;
		return true;
	}
}