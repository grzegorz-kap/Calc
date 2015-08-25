#include "stdafx.h"
#include "TokenList.h"

namespace KLab {
	TokenList::TokenList() {
	}

	TokenList::~TokenList() {
	}

	void TokenList::push(std::unique_ptr<Token> &&token) {
		tokens.push_back(std::move(token));
	}

	Token& TokenList::back() {
		return tokens->back();
	}

	int TokenList::size() const {
		return tokens.size();
	}

	vector<unique_ptr<Token>> TokenList::getTokens() {
		return std::move(tokens);
	}
}