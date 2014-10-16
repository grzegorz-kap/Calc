#include "stdafx.h"
#include "Parser.h"

namespace PR
{
	void Parser::changeIfAssignment()
	{
		if (onp.size() < 3)
			return;

		if (onp.back()->getLexemeR() != "=" && (onp.back()->getClass() != TOKEN_CLASS::OUTPUT_OFF || onp.rbegin()[1]->getLexemeR() != "="))
			return;

		auto ptr = make_unique<Assignment>();
		ptr->loadTarget(onp);
		onp.insert(onp.begin(), std::move(ptr));
	}
}