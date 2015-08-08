#include "stdafx.h"
#include "InstructionFor.h"

namespace KLab
{
	InstructionFor::InstructionFor()
	{
		set_class(TOKEN_CLASS::FOR_KEYWORD);
	}

	InstructionFor::InstructionFor(const Token &token)
		:Token(token)
	{
	}

	InstructionFor::~InstructionFor()
	{
	}

	void InstructionFor::setName(const string &new_name)
	{
		name = new_name;
	}

	void InstructionFor::setOnp(const vector<shared_ptr<Token>> &o)
	{
		onp = o;
	}

	void InstructionFor::setOnp(vector<shared_ptr<Token>> &&o)
	{
		onp = std::move(o);
	}

	const vector<shared_ptr<Token>>& InstructionFor::getOnp() const
	{
		return onp;
	}

	string InstructionFor::getLexeme() const
	{
		return name;
	}
}