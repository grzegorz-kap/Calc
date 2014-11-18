#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	void CodeExecutor::onID()
	{
		try{
			if (ip->size() == 1)
			{
				assignment.push_back({ vars_ref.getIterator((*i)->getLexemeR()), false });
				assignment_flag = true;
			}
			else
				stack.push_back(vars_ref.get((*i)->getLexemeR()));
		}
		catch (const string &ex)
		{
			if (!onScript())
				throw CalcException("Undefined variable or script '" + (*i)->getLexemeR() + "'.", (*i)->getPosition());
		}		
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