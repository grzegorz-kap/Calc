#pragma once
#include "Data.h"
#include "Token.h"

namespace PR
{
	class String : public Token
	{
		string data;
	public:
		String(const string &str);
		String(string &&str);
		~String();
	};
}

