#include "stdafx.h"
#include "TokenizerService.h"

namespace KLab {
	
	TokenizerService::TokenizerService() {
	}

	TokenizerService::~TokenizerService() {
	}

	shared_ptr<TokenList> TokenizerService::readTokens(string inputText) {
		return readTokens(shared_ptr<TokenizerContext>(new TokenizerContext(inputText)));
	}

	shared_ptr<TokenList> TokenizerService::readTokens(const shared_ptr<TokenizerContext> &tokenizerContext) {
		context = tokenizerContext;
		process();
		return context->Tokens();
	}

	void TokenizerService::process() {
		while (context->isCharacterToProccess()) {
			if (context->isNumberStart())
				onNumber();
			else if (context->isWordStart())
				onWord();
			else if (context->isSpaceStart())
				onSpace();
			else if (context->isNewLineStart())
				onNewLine();
			else if (context->isSingleLineCommentStart())
				onSingleLineComment();
			else if (context->isMultiLineCommentStart())
				onMultiLineCommentStart();
			else if (checkForOperatorAndReact())
				continue;
			else if (checkForOtherSymbolsAndReact())
				continue;
			else
				throw TokenizeException("Symbol unknown.", context);
		}
	}
}