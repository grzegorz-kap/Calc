#pragma once

#include <string>
#include <memory>

#include "TokenList.h"

using std::string;

namespace KLab {
	class TokenizerContext {
	private:
		shared_ptr<TokenList> tokenList;
		string text;
		int length;
		int index;

	public:
		TokenizerContext(const string& inputText);
		TokenizerContext(string &&inputText);
		~TokenizerContext();

		bool EoI() const;
		char at(int index) const;
		char last() const;
		int getIndex() const;
		int getLength() const;
		string& getTextRef();
		void decrementLength(int value);
		void increment(int value);

		void pushToken(unique_ptr<Token> &&token);
		int tokensCount() const;
		Token& tokensBack();
		shared_ptr<TokenList> getTokens();

	private:
		void init();
	};
}
