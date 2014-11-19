#pragma once

#include <string>
#include <vector>
#include <memory>

using std::vector;
using std::string;
using std::shared_ptr;

#include "Token.h"

namespace PR
{
	class ExternalFunction
	{
		vector<string> output;					/* Output arguments names */
		vector<string> input;					/* Input arguments names */
		string name;							/* Function name */
		vector<vector<shared_ptr<Token>>> body; /* Function code */
		bool updated;							/* If true , reload function before use */
	
	public:
		ExternalFunction();
		~ExternalFunction();
		
		void set_updated();
		void reset_updated();
		bool getUpdated();
		void addOutput(string &&name);
		void addOutput(const string &name);
		void addInput(string &&name);
		void addInput(const string &name);
		void setName(string &&nameA);
		void setName(const string &nameA);
		const string & getName() const;
		const vector<string>& getInput()const;
		const vector<string>& getOutput() const;
		const vector<vector<shared_ptr<Token>>> & getCode() const;
		void addInstruction(vector<shared_ptr<Token>> &&in);
	};
}

