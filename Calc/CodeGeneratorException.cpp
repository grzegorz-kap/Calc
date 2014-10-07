#include "stdafx.h"
#include "CodeGeneratorException.h"


namespace PR
{
	CodeGeneratorException::CodeGeneratorException(const string &description)
		:CalcException(description)
	{
	}


	CodeGeneratorException::~CodeGeneratorException()
	{
	}
}
