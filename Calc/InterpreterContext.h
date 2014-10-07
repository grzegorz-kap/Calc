#pragma once

#include <string>
#include <vector>

#include "TokensTypes.h"

namespace PR
{
	using std::string;
	using std::vector;

	class InterpreterContext
	{
		
	public:
		static InterpreterContext* getInstance();
		bool isKeyword(const string &word) const;
		bool isInternalFunction(const string &word) const;
		bool isExternalFunction(const string &word) const;
		TOKEN_CLASS identiferType(const string &word) const;
	private:
		InterpreterContext();
		~InterpreterContext();

		static InterpreterContext *instance;

		vector<string> keywords;
		vector<string> internalFunctions;
		vector<string> externalFunctions;

		void setUpKeywords();
		void setUpInternalFunctions();
		void setUpExternalFunctions();
	};

}


