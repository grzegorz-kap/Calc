#include "stdafx.h"
#include "NumericException.h"


namespace PR
{
	NumericException::NumericException(std::string &&message)
		:message(std::move(message))
	{
	}


	NumericException::~NumericException()
	{
	}

	void NumericException::throwMatrixMultDimensions()
	{
		throw NumericException(string("Error using *\n Matrix dimensions must agree"));
	}
}
