#include "RegexTokenizerService.h"

namespace KLab {
	RegexTokenizerService::RegexTokenizerService(const string &input) : TokenizerService(input) {
	}

	RegexTokenizerService::~RegexTokenizerService() {
	}

	RegexTokenizerService::RegexTokenizerService(string &&input) : TokenizerService(std::move(input)) {
	}

	void RegexTokenizerService::onNumber() {
		string result = tokenizerContextService.read(NUMBER_REGEX);
		tokenizerContext.pushToken(make_unique<SNumber>(Token(NumberReader::read(tokenizerContext.getTextRef(), tokenizerContext.getIndex()), TOKEN_CLASS::NUMBER)));
		setLine();
		inc(tokenizerContext.tokensBack().getLexemeR().size());
	}
}