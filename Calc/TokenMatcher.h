#pragma once

#include "TokenizerContext.h"
#include "CharHelper.h"

namespace KLab {
	class TokenMatcher {
		const TokenizerContext &context;

	public:
		TokenMatcher(const TokenizerContext &context);
		~TokenMatcher();

		bool isNumberStart();
		bool isWordStart();
		bool isSpaceStart();
		bool isNewLineStart();
		bool isSingleLineCommentStart();
		bool isMultiLineCommentStart();
	};
}
