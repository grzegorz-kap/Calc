#pragma once

#include "export.h"
#include "commons.h"
#include "TokenList.h"
#include "TokenizedText.h"

namespace KLab
{
	class CALC_TEST_API TokenizerContext {
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
		string at(int offset, int length) const;
		bool at(int offset, char character) const;
		bool at(int offset, int length, const string &compare) const;
		char at(int offset = 0) const;
		const string& getText() const;
		shared_ptr<TokenList> getTokens() const;
		void addToken(unique_ptr<Token> &&token);;
		void incrementPosition(int value);
		void setLine(int value);
		int getLine() const;
		void setColumn(int value);
		int getColumn() const;

	private:
		void setupInitialState();
	};
}
