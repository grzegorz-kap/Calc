#pragma once
#include "CalcException.h"

#include <string>

using std::string;

namespace KLab
{
	class CodeGeneratorException :
		public CalcException
	{
	public:
		CodeGeneratorException(const string &description);
		~CodeGeneratorException();
	};
}
