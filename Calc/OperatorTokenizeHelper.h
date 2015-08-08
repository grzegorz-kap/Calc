#pragma once

#include "commons.h"

#include "TokenClass.h"
#include "TokenizerContext.h"

namespace KLab {
	class OperatorTokenizeHelper {
		const static vector<string> OPERATOR_TOKENS;

	public:
		OperatorTokenizeHelper() = delete;
		static bool findOperator(string &result, const TokenizerContext &tokenizerContext);
	};
}
