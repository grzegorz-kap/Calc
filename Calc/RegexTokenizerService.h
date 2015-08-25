#pragma once

#include <regex>
#include <string>

#include "TokenizerService.h"

using std::regex;
using std::string;

namespace KLab {
	class RegexTokenizerService : public TokenizerService {
	public:
		static const string NUMBER_PATTERN;

		static const regex NUMBER_REGEX;

		RegexTokenizerService(const string &input);
		RegexTokenizerService(string &&input);
		~RegexTokenizerService();

	protected:
		virtual void onNumber() override;
	};
}
