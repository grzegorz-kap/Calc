  #pragma once
#include "export.h"
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <memory>

using std::string;
using std::cout;

#include "CodeExecutor.h"

namespace PR
{
	class CALC_API Interpreter
	{
		static Variables main_vars;
	public:
		Interpreter();
		~Interpreter();
		void work(const string &command);
		void workFromFile(const string &fileName);
		void connectStopComputing();

		void updateFile(const char *);
		void changeWorkingDirectory(const char *dir);
		
		VariableInfo getVariableInfo(const char *name);

	private:
		void sendUpdatedVariablesInformations();
	};
}

