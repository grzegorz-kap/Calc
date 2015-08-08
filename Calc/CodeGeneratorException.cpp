#include "stdafx.h"
#include "CodeGeneratorException.h"

namespace KLab
{
	CodeGeneratorException::CodeGeneratorException(const string &description)
		:CalcException(description)
	{
	}

	CodeGeneratorException::~CodeGeneratorException()
	{
	}
}