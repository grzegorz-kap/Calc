#include "stdafx.h"
#include "ExternalFunction.h"


namespace PR
{
	ExternalFunction::ExternalFunction()
	{
	}


	ExternalFunction::~ExternalFunction()
	{
	}

	void ExternalFunction::addInstruction(Instruction &&in)
	{
		body.push_back(vector<shared_ptr<Token>>(in.size()));
		for (int i = in.size() - 1; i >= 0; i--)
		{
			body.back()[i] = shared_ptr<Token>(in[i].release());
		}
	}
}
