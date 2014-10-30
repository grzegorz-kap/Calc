#include "stdafx.h"
#include "Parser.h"

namespace PR
{
	void Parser::changeIfAssignment()
	{
		if (onp.size() < 3)
			return;

		bool find = false;
		if (onp.back()->getLexemeR() == "=")
		{
			find = true;
			onp.back()->set_class(TOKEN_CLASS::ASSIGNMENT);
		}

		if (!find && onp.back()->getClass() == TOKEN_CLASS::OUTPUT_OFF && onp.rbegin()[1]->getLexemeR() == "=")
		{
			find = true;
			onp.rbegin()[1]->set_class(TOKEN_CLASS::ASSIGNMENT);
		}

		if (!find)
			return;

		Assignment assignment;
		assignment.loadTarget(onp);
		unique_ptr<Assignment> ptr = std::make_unique<Assignment>(assignment);
		onp.insert(onp.begin(), std::move(ptr));
	}
}