#pragma once

#include <regex>
#include <string>

#include "TokenizerContext.h"

namespace KLab {
	class TokenizerContextService {
	private:
		TokenizerContext& tokenizerContext;
	public:
		TokenizerContextService(TokenizerContext& tokenizerContext);
		~TokenizerContextService();

		string read(const std::regex &regexExpression);
	};
}
