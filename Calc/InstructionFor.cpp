#include "stdafx.h"
#include "InstructionFor.h"


namespace PR
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
}
