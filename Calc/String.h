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

		virtual const string & getLexemeR() const override;
		virtual string getLexeme() const override;
		virtual string toString() const override;
		virtual string toHtml() const override;
		virtual string getValueInfoString() const override;
		virtual shared_ptr<Data> copy() const override;
		
		virtual shared_ptr<Data> operator + (shared_ptr<Data> &b) const override;
	};
}

