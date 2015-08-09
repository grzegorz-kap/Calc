#include "stdafx.h"
#include "RegexTokenizerService.h"

namespace KLab
{
	const string RegexTokenizerService::NUMBER_PATTERN = "((\\d+([.]\\d*)?)|([.]\\d+))([eE][-+]?\\d+)?i?";
	const string RegexTokenizerService::WORD_PATTERN = "[a-zA-Z_][a-zA-Z0-9_]*";
	const string RegexTokenizerService::SPACE_PATTERN = "[\\t ]+";
	const string RegexTokenizerService::NEW_LINE_PATTERN = "\\n[\\n \\t]*";
	const string RegexTokenizerService::SINGLELINE_COMMENT_PATTERN = "((//)|[%]).*";
	const string RegexTokenizerService::MULTILINE_COMMENT_PATTERN = "%\\{.+?%\\}";

	const regex RegexTokenizerService::NUMBER_REGEX = regex(NUMBER_PATTERN, regex::optimize);
	const regex RegexTokenizerService::WORD_REGEX = regex(WORD_PATTERN, regex::optimize);
	const regex RegexTokenizerService::SPACE_REGEX = regex(SPACE_PATTERN, regex::optimize);
	const regex RegexTokenizerService::NEW_LINE_REGEX = regex(NEW_LINE_PATTERN, regex::optimize);
	const regex RegexTokenizerService::SINGLELINE_COMMENT_REGEX = regex(SINGLELINE_COMMENT_PATTERN, regex::optimize);
	const regex RegexTokenizerService::MULTILINE_COMMENT_REGEX = regex(MULTILINE_COMMENT_PATTERN, regex::optimize);

	RegexTokenizerService::RegexTokenizerService() {
	}

	RegexTokenizerService::~RegexTokenizerService() {
	}

	void RegexTokenizerService::onNumber() {
		contextService->addTokenToContext(NUMBER_REGEX, TOKEN_CLASS::NUMBER);
	}

	void RegexTokenizerService::onWord() {
		contextService->addTokenToContext(WORD_REGEX, TOKEN_CLASS::WORD);
	}

	void RegexTokenizerService::onSpace() {
		contextService->addTokenToContext(SPACE_REGEX, TOKEN_CLASS::SPACE);
	}

	void RegexTokenizerService::onNewLine() {
		contextService->addTokenToContext(NEW_LINE_REGEX, TOKEN_CLASS::NEW_LINE);
	}

	void RegexTokenizerService::onSingleLineComment() {
		contextService->addTokenToContext(SINGLELINE_COMMENT_REGEX, TOKEN_CLASS::SINGLELINE_COMMENT);
	}

	void RegexTokenizerService::onMultiLineCommentStart() {
		contextService->addTokenToContext(MULTILINE_COMMENT_REGEX, TOKEN_CLASS::MULTILINE_COMMENT);
	}

	bool RegexTokenizerService::checkForOperatorAndReact() {
		string op = "";
		if (tokenMatcher->matchOperator(op)) {
			contextService->addTokenToContext(op, TOKEN_CLASS::OPERATOR);
			return true;
		}
		return false;
	}

	bool RegexTokenizerService::checkForOtherSymbolsAndReact() {
		TOKEN_CLASS tokenClass;
		char character;
		if (tokenMatcher->matchOtherSymbol(tokenClass, character)) {
			contextService->addTokenToContext(string(character, 1), tokenClass);
			return true;
		}
		return false;
	}
}