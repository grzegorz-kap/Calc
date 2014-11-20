#include "stdafx.h"
#include "String.h"


namespace PR
{
	String::String(const string &str)
		:data(str)
	{
		_type = TYPE::STRING;
		set_class(TOKEN_CLASS::STRING);
	}

	String::String(string &&str)
		: data(std::move(str))
	{
		_type = TYPE::STRING;
		set_class(TOKEN_CLASS::STRING);
	}


	String::~String()
	{
	}
}
