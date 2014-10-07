  #pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <memory>

using std::string;
using std::cout;

#include "export.h"
#include "LexicalAnalyzer.h"
#include "InterpreterContext.h"
#include "Parser.h"
#include "CalcException.h"

#include "Matrix.h"
#include "CodeExecutor.h"

namespace PR
{
	class CALC_API Interpreter
	{
		
	public:
		Interpreter();
		~Interpreter();
		string work(const string &command);
		string workFromFile(const string &fileName);
	};
}

