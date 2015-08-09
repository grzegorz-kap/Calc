#include "stdafx.h"
#include "TokenizerService.h"

namespace KLab {
	TokenizerService::TokenizerService() {
	}

	TokenizerService::~TokenizerService() {
	}

	shared_ptr<TokenList> TokenizerService::readTokens(string inputText) {
		tokenizerContext = std::make_shared<TokenizerContext>(inputText);
		tokenMatcher.reset(new TokenMatcher(*tokenizerContext));
		contextService.reset(new TokenizerContextService(tokenizerContext.get()));
		process();
		return tokenizerContext->getTokens();
	}

	void TokenizerService::process() {
		while (contextService->isCharacterToProccess()) {
			if (tokenMatcher->isNumberStart())
				onNumber();
			else if (tokenMatcher->isWordStart())
				onWord();
			else if (tokenMatcher->isSpaceStart())
				onSpace();
			else if (tokenMatcher->isNewLineStart())
				onNewLine();
			else if (tokenMatcher->isSingleLineCommentStart())
				onSingleLineComment();
			else if (tokenMatcher->isMultiLineCommentStart())
				onMultiLineCommentStart();
			else if (checkForOperatorAndReact())
				continue;
			else if (checkForOtherSymbolsAndReact())
				continue;
			else
				throw TokenizeException("Symbol unknown.", tokenizerContext);
		}
	}
}