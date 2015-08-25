#pragma once

#include <vector>
#include <memory>

#include "Token.h"

using std::vector;
using std::unique_ptr;

namespace KLab {
	class TokenList {
	private:
		vector<unique_ptr<Token>> tokens;

	public:
		TokenList();
		TokenList(const TokenList& copy) = delete;
		TokenList& operator = (const TokenList& copy) = delete;
		~TokenList();

		void push(std::unique_ptr<Token> &&token);
		Token& back();
		int size() const;

		vector<unique_ptr<Token>> getTokens();
	};
}
