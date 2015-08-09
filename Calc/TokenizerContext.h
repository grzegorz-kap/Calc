#pragma once

#include "commons.h"

#include "TokenList.h"
#include "TokenizedText.h"

namespace KLab
{
	class TokenizerContext {
		shared_ptr<TokenList> tokens;
		TokenizedText text;
		int line;
		int column;
	public:

		TokenizerContext(string inputText);
		~TokenizerContext();
		int textPosition() const;
		int textLength() const;
		bool isCharacterToProccess();
		void put(unique_ptr<Token> &&token);
		void put(const string &lexame, TOKEN_CLASS tokenClass);
		void put(string &&lexame, TOKEN_CLASS tokenClass);

		char at(int offset = 0) const;
		string at(int offset, int length) const;
		bool at(int offset, char character) const;
		bool at(int offset, int length, const string &compare) const;
		shared_ptr<TokenList> getTokens() const;
		const string& getText() const;

	private:
		void setupInitialState();
		void proccessBeforePut(Token &token);
		void updateColumnAndLine(const Token &token);
		void onNewLine(int tokenLength);
		void onMultilineComment(const Token &token);
	};
}
