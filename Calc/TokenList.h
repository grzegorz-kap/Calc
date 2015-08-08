#pragma once

#include "commons.h"

#include "Token.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;

namespace KLab
{
	class TokenList {
	private:
		vector<unique_ptr<Token>> tokens;
	public:
		TokenList();
		TokenList(int capacity);
		TokenList(const TokenList &secondList);
		~TokenList();

		virtual TokenList& operator = (const TokenList& second);
		void add(unique_ptr<Token> &&token);

	private:
		void copyTokens(const TokenList &second);
	};
}
