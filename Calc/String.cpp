#include "stdafx.h"
#include "String.h"

namespace KLab
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

	const string& String::getLexemeR() const
	{
		return data;
	}

	string String::getLexeme() const
	{
		return data;
	}

	string String::toString() const
	{
		return data;
	}

	string String::toStringCommpact() const
	{
		return "'" + data + "'";
	}

	string String::toHtml() const
	{
		return data;
	}

	string String::getValueInfoString() const
	{
		return data;
	}

	shared_ptr<Data> String::copy() const
	{
		return make_shared<String>(*this);
	}

	shared_ptr<Data> String::operator + (shared_ptr<Data> &b) const
	{
		return make_shared<String>(data + std::dynamic_pointer_cast<String>(b)->data);
	}
}