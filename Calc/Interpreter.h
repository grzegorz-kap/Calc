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
#include "Parser.h"
#include "CodeExecutor.h"
#include "CodeGenerator.h"

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

