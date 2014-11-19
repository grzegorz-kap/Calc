#include "stdafx.h"
#include "ShortCircuitJumper.h"


namespace PR
{
	ShortCircuitJumper::ShortCircuitJumper(TOKEN_CLASS _class)
		:Token(_class)
	{
	}


	ShortCircuitJumper::~ShortCircuitJumper()
	{
	}

	void ShortCircuitJumper::setJumpOnFalse(int value)
	{
		jump_on_false = value;
	}

	void ShortCircuitJumper::setJumpOnTrue(int value)
	{
		jump_on_true = value;
	}

	int ShortCircuitJumper::getJumpOn(bool val) const
	{
		return val ? jump_on_true : jump_on_false;
	}

	int ShortCircuitJumper::getJumpOnTrue() const
	{
		return jump_on_true;
	}

	int ShortCircuitJumper::getJumpOnFalse() const
	{
		return jump_on_false;
	}
}