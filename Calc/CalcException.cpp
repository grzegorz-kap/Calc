#include "stdafx.h"
#include "CalcException.h"


namespace PR
{
	CalcException::CalcException(const string &messageA,const string &commandA, int positionA)
		:message(messageA),
		command(commandA),
		position(positionA)
	{
	}

	CalcException::CalcException(const string &mess, int positionA)
		:message(mess), position(positionA)
	{
	}


	CalcException::~CalcException()
	{
	}

}