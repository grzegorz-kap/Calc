#pragma once

#include "TokenizerContext.h"
#include "TokenizeException.h"

namespace KLab {
	class TokenizerService {
	protected:
		shared_ptr<TokenizerContext> context;

	public:
		TokenizerService();
		~TokenizerService();
		shared_ptr<TokenList> readTokens(string inputText);
		shared_ptr<TokenList> readTokens(const shared_ptr<TokenizerContext> &tokenizerContext);

	protected:

		virtual void onNumber() = 0;
		virtual void onWord() = 0;
		virtual void onSpace() = 0;
		virtual void onNewLine() = 0;
		virtual void onSingleLineComment() = 0;
		virtual void onMultiLineCommentStart() = 0;
		virtual bool checkForOperatorAndReact() = 0;
		virtual bool checkForOtherSymbolsAndReact() = 0;

	private:
		void process();
	};
}
