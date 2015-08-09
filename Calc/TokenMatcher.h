#pragma once

#include "TokenizerContext.h"
#include "CharHelper.h"
#include "OperatorTokenizeHelper.h"
#include "SymbolsTokenizeHelper.h"

namespace KLab {
	class TokenMatcher {
		const TokenizerContext &context;

	public:
		TokenMatcher(const TokenizerContext &context);
		~TokenMatcher();

		bool isNumberStart() const;
		bool isWordStart() const;
		bool isSpaceStart() const;
		bool isNewLineStart() const;
		bool isSingleLineCommentStart() const;
		bool isMultiLineCommentStart() const;
		bool matchOperator(string &result) const;
		bool matchOtherSymbol(TOKEN_CLASS &result, char &character) const;
	};
}
