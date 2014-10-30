  #pragma once
#include "export.h"
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <memory>

using std::string;
using std::cout;


#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "CodeExecutor.h"
#include "CodeGenerator.h"

namespace PR
{
	class CALC_API Interpreter
	{
		static variables main_vars;
	public:
		Interpreter();
		~Interpreter();
		void work(const string &command);
		void workFromFile(const string &fileName);
		void connectStopComputing();

		void updateFile(const char *);
	};
}

