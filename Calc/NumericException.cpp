#include "stdafx.h"
#include "NumericException.h"

namespace KLab
{
	NumericException::NumericException(std::string &&message)
		:CalcException(message)
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

	void NumericException::throwMatrixLogDimensions()
	{
		throw NumericException(string("Logarithm base has to be scalar"));
	}

	void NumericException::throwLuNotSquare()
	{
		throw NumericException(string("LU decomposition error, intput matrix is not square"));
	}

	void NumericException::throwIndexOutOfRange()
	{
		throw NumericException(string("Index exceeds matrix dimensions."));
	}

	void NumericException::throwIndexMustBeReal()
	{
		throw NumericException(string("Subscript indices must either be real positive integers or logicals."));
	}
}