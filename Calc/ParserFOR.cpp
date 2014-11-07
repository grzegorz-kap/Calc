#include "stdafx.h"
#include "Parser.h"

namespace PR
{
	void Parser::onKeywordFOR()
	{
		unique_ptr<InstructionFor> _for = make_unique<InstructionFor>(*i);
		iter++;

		if (iter == tokens.end())
			throw CalcException("Unexpected end of code", i->getPosition());

		parse();

		if (onp.size() < 3)
			throw CalcException("Error parsing 'for' keyword", i->getPosition());

		AssignmentSingle * assignment = dynamic_cast<AssignmentSingle *>(onp.front().get());
		if (assignment == nullptr)
			throw CalcException("Error in for instruction,single assignment not found!");
		_for->setName(assignment->getLexeme());
		onp.erase(onp.begin());

		if (onp.back()->getClass() == TOKEN_CLASS::OUTPUT_OFF)
			onp.pop_back();
		if (onp.back()->getClass() == TOKEN_CLASS::ASSIGNMENT)
			onp.pop_back();

		if (onp.size() == 0 )
			throw CalcException("Error parsing 'for' keyword", i->getPosition());

		_for->setOnp(std::move(onp));
		onp.push_back(std::move(_for));
		iterBack();
	}
}