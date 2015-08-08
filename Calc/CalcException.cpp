#include "stdafx.h"
#include "CalcException.h"

namespace PR
{
	CalcException::CalcException(const string &messageA, const string &commandA, int positionA, int line)
		:message(messageA),
		command(commandA),
		position(positionA),
		line(line)
	{
	}

	CalcException::CalcException(const string &mess, int positionA)
		:message(mess), position(positionA)
	{
		line = 0;
	}

	CalcException::~CalcException()
	{
	}

	string CalcException::getFullMessage() const
	{
		return "Ln: " + std::to_string(line) + ", Col: " + std::to_string(position) + "\n" + message;
	}
}