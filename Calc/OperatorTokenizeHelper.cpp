#include "stdafx.h"
#include "OperatorTokenizeHelper.h"

namespace KLab {
	/* order meters */
	decltype(OperatorTokenizeHelper::OPERATOR_TOKENS) OperatorTokenizeHelper::OPERATOR_TOKENS = {
		"==", "=", "*", "/", "-", "+"
	};

	bool OperatorTokenizeHelper::findOperator(string &result, const TokenizerContext &context) {
		auto iter = std::find_if(OPERATOR_TOKENS.cbegin(), OPERATOR_TOKENS.cend(), [&context](const string &value){
			return value.compare(0, value.size(), context.getText(), context.textPosition(), value.size()) == 0;
		});

		if (iter != OPERATOR_TOKENS.end()) {
			result = *iter;
			return true;
		}
		return false;
	}
}