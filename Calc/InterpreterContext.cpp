#include "stdafx.h"
#include "InterpreterContext.h"

PR::InterpreterContext* PR::InterpreterContext::instance = nullptr;

namespace PR
{
	InterpreterContext* InterpreterContext::getInstance()
	{
		if (instance == nullptr)
			instance = new InterpreterContext();
		return instance;
	}

	TOKEN_CLASS InterpreterContext::identiferType(const string &id) const
	{
		if (isKeyword(id))
			return TOKEN_CLASS::KEY_WORD;
		else
			return TOKEN_CLASS::ID;
	}

	bool InterpreterContext::isExternalFunction(const string &word) const
	{
		for (int i = externalFunctions.size()-1; i >= 0; i--)
		{
			if (externalFunctions[i] == word)
				return true;
		}
		return false;
	}

	bool InterpreterContext::isInternalFunction(const string &word) const 
	{
		for (int i = internalFunctions.size() - 1; i >= 0; i--)
		{
			if (internalFunctions[i] == word)
				return true;
		}
		return false;
	}

	bool InterpreterContext::isKeyword(const string &word) const
	{
		for (int i = keywords.size() - 1; i >= 0; i--)
		{
			if (keywords[i] == word)
				return true;
		}
		return false;
	}

	InterpreterContext::InterpreterContext()
	{
		setUpKeywords();
		setUpInternalFunctions();
		setUpExternalFunctions();
	}

	InterpreterContext::~InterpreterContext()
	{
	}

	void InterpreterContext::setUpKeywords()
	{
		keywords = {
			"if", "else", "function", "for", "while", "break", "continue", "return", "end", "endfunction"
		};
	}

	void InterpreterContext::setUpInternalFunctions()
	{
		internalFunctions = {
			"det", "rand", "sqrt"
		};
	}

	void InterpreterContext::setUpExternalFunctions()
	{
		externalFunctions = {
			"in"
		};
	}
}
