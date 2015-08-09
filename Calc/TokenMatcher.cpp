#include "stdafx.h"
#include "TokenMatcher.h"

namespace KLab {
	TokenMatcher::TokenMatcher(const TokenizerContext &context) :
		context(context) {
	}

	TokenMatcher::~TokenMatcher() {
	}

	bool TokenMatcher::isNumberStart() {
		return CharHelper::isDigit(context.at()) || context.at(0, '.') && CharHelper::isDigit(context.at(1));
	}

	bool TokenMatcher::isWordStart() {
		return CharHelper::isLetter(context.at()) || context.at(0, '_');
	}

	bool TokenMatcher::isSpaceStart() {
		return context.at(0, ' ') || context.at(0, '\t');
	}

	bool TokenMatcher::isNewLineStart() {
		return context.at(0, '\n');
	}

	bool TokenMatcher::isSingleLineCommentStart() {
		return context.at(0, '%') && !context.at(1, '{') || context.at(0, 2, "//");
	}

	bool TokenMatcher::isMultiLineCommentStart() {
		return context.at(0, 2, "%{");
	}
}