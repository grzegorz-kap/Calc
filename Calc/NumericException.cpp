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

	void NumericException::throwLogarithmFromZero()
	{
		throw NumericException(string("Logarithm of 0!"));
	}

	void NumericException::throwLogarithmZeroBase()
	{
		throw NumericException(string("Logarithm base is 0!"));
	}
}
