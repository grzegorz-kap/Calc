#pragma once

#include "TokenizerService.h"
#include "OperatorTokenizeHelper.h"
#include "SymbolsTokenizeHelper.h"

namespace KLab
{
	class RegexTokenizerService : public TokenizerService {
	public:
		const static string NUMBER_PATTERN;
		const static string WORD_PATTERN;
		const static string SPACE_PATTERN;
		const static string NEW_LINE_PATTERN;
		const static string SINGLELINE_COMMENT_PATTERN;
		const static string MULTILINE_COMMENT_PATTERN;

	private:
		const static regex NUMBER_REGEX;
		const static regex WORD_REGEX;
		const static regex SPACE_REGEX;
		const static regex NEW_LINE_REGEX;
		const static regex SINGLELINE_COMMENT_REGEX;
		const static regex MULTILINE_COMMENT_REGEX;

	public:

		RegexTokenizerService();
		~RegexTokenizerService();

	private:
		virtual void onNumber() override;
		virtual void onWord() override;
		virtual void onSpace() override;
		virtual void onNewLine() override;
		virtual void onSingleLineComment() override;
		virtual void onMultiLineCommentStart() override;
		virtual bool checkForOperatorAndReact() override;
		virtual bool checkForOtherSymbolsAndReact() override;

		void readToken(const regex &reg, TOKEN_CLASS tokenClass);
	};
}
