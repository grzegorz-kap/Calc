#pragma once

#include <vector>
#include <memory>
#include <string>

using std::vector;
using std::shared_ptr;
using std::string;

#include "Token.h"

namespace PR
{
	class InstructionFor :
		public Token
	{
		vector<shared_ptr<Token>> onp;
		string name ;
	public:
		InstructionFor();
		InstructionFor(const Token &token);
		~InstructionFor();

		void setName(const string &new_name){ name = new_name; }
		void setOnp(const vector<shared_ptr<Token>> &o){ onp = o; }
		void setOnp(vector<shared_ptr<Token>> &&o){ onp = std::move(o); }

		const vector<shared_ptr<Token>>& getOnp() const { return onp; }

		virtual string getLexeme() const override { return name; };
	};
}

