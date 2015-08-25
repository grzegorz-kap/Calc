#include "stdafx.h"
#include "TokenizerContextService.h"

namespace KLab {
	TokenizerContextService::TokenizerContextService(TokenizerContext& tokenizerContext) :
		tokenizerContext(tokenizerContext) {
	}

	TokenizerContextService::~TokenizerContextService() {
	}

	string TokenizerContextService::read(const std::regex &regexExpression) {
		const string& text = tokenizerContext.getTextRef();
		std::smatch match;
		bool result = std::regex_search(text.cbegin() + tokenizerContext.getIndex(), text.cend(), match, regexExpression);
		return result ? match[0] : string("");
	}
}