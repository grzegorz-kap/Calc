#include "stdafx.h"
#include "TokenMatcher.h"

namespace KLab {
	TokenMatcher::TokenMatcher(const TokenizerContext &context) :
		context(context) {
	}

	TokenMatcher::~TokenMatcher() {
	}

	bool TokenMatcher::isNumberStart() const {
		return CharHelper::isDigit(context.at()) || context.at(0, '.') && CharHelper::isDigit(context.at(1));
	}

	bool TokenMatcher::isWordStart() const {
		return CharHelper::isLetter(context.at()) || context.at(0, '_');
	}

	bool TokenMatcher::isSpaceStart() const {
		return context.at(0, ' ') || context.at(0, '\t');
	}

	bool TokenMatcher::isNewLineStart() const {
		return context.at(0, '\n');
	}

	bool TokenMatcher::isSingleLineCommentStart() const {
		return context.at(0, '%') && !context.at(1, '{') || context.at(0, 2, "//");
	}

	bool TokenMatcher::isMultiLineCommentStart() const {
		return context.at(0, 2, "%{");
	}

	bool TokenMatcher::matchOperator(string &result) const {
		return OperatorTokenizeHelper::findOperator(result, context);
	}

	bool TokenMatcher::matchOtherSymbol(TOKEN_CLASS &result, char& character) const {
		character = context.at(0);
		return SymbolsTokenizeHelper::find(result, character);
	}
}