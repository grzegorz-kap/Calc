#pragma once

#include <string>
#include <vector>

#include "CodeGenerator.h"

using namespace std;

namespace PR
{
	class ExternalFunction
	{
		vector<string> output;
		vector<string> input;
		string name;
		vector<vector<shared_ptr<Token>>> body;
		bool updated;
	public:
		void set_updated(){ updated = true; }
		void reset_updated(){ updated = false; }
		bool getUpdated(){ return updated; }

		void addOutput(string &&name){ output.push_back(std::move(name)); }
		void addOutput(const string &name){ output.push_back(name); }
		void addInput(string &&name){ input.push_back(std::move(name)); }
		void addInput(const string &name){ input.push_back(name); }
		void setName(string &&nameA){ name = std::move(nameA); }
		void setName(const string &nameA){ name = nameA; }

		void addInstruction(Instruction &&in);
	

		ExternalFunction();
		~ExternalFunction();
	};
}

