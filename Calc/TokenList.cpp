#include "stdafx.h"
#include "TokenList.h"

namespace KLab
{
	TokenList::TokenList() {
	}

	TokenList::TokenList(int capacity) {
		tokens.reserve(capacity);
	}

	TokenList::TokenList(const TokenList &secondList) {
		copyTokens(secondList);
	}

	TokenList::~TokenList() {
	}

	void TokenList::add(unique_ptr<Token> &&token) {
		tokens.push_back(std::move(token));
	}

	TokenList& TokenList::operator=(const TokenList& second) {
		if (this != &second) {
			tokens.clear();
			copyTokens(second);
		}
		return *this;
	}

	void TokenList::copyTokens(const TokenList &second) {
		tokens.reserve(second.tokens.size());
		for (const auto &token : second.tokens) {
			tokens.push_back(make_unique<Token>(*token));
		}
	}
}