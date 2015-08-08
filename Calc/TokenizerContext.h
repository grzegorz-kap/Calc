#pragma once

#include <algorithm>

#include "TokenList.h"
#include "TokenizedText.h"
#include "CharHelper.h"

namespace KLab
{
	class TokenizerContext {
		TokenList tokens;
		TokenizedText text;
		int line;
		int column;
	public:

		TokenizerContext(string inputText);
		~TokenizerContext();

		int textPosition() const;

		bool isCharacterToProccess();

		void put(unique_ptr<Token> &&token);

		bool isNumberStart();

		bool isWordStart();

		bool isSpaceStart();

		bool isNewLineStart();

		bool isSingleLineCommentStart();

		bool isMultiLineCommentStart();

		char at(int offset = 0);

		string at(int offset, int length);

		void setupInitialState();

		void proccessBeforePut(Token &token);

		void updateColumnAndLine(const Token &token);

		void onNewLine(int tokenLength);

		void onMultilineComment(const Token &token);
	};
}
