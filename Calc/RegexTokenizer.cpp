#include "stdafx.h"
#include "RegexTokenizer.h"

namespace KLab
{
	const string RegexTokenizer::NUMBER_PATTERN = "((\\d+([.]\\d*)?)|([.]\\d+))([eE][-+]?\\d+)?i?";
	const string RegexTokenizer::WORD_PATTERN = "[a-zA-Z_][a-zA-Z0-9_]*";
	const string RegexTokenizer::SPACE_PATTERN = "[\\t ]+";
	const string RegexTokenizer::NEW_LINE_PATTERN = "\\n[\\n \\t]*";
	const string RegexTokenizer::SINGLELINE_COMMENT_PATTERN = "((//)|[%]).*";
	const string RegexTokenizer::MULTILINE_COMMENT_PATTERN = "%\\{.+?%\\}";

	const regex RegexTokenizer::NUMBER_REGEX = regex(NUMBER_PATTERN, regex::optimize);
	const regex RegexTokenizer::WORD_REGEX = regex(WORD_PATTERN, regex::optimize);
	const regex RegexTokenizer::SPACE_REGEX = regex(SPACE_PATTERN, regex::optimize);
	const regex RegexTokenizer::NEW_LINE_REGEX = regex(NEW_LINE_PATTERN, regex::optimize);
	const regex RegexTokenizer::SINGLELINE_COMMENT_REGEX = regex(SINGLELINE_COMMENT_PATTERN, regex::optimize);
	const regex RegexTokenizer::MULTILINE_COMMENT_REGEX = regex(MULTILINE_COMMENT_PATTERN, regex::optimize);

	RegexTokenizer::RegexTokenizer() {
	}

	RegexTokenizer::~RegexTokenizer() {
	}

	void RegexTokenizer::onNumber() {
		readToken(NUMBER_REGEX, TOKEN_CLASS::NUMBER);
	}

	void RegexTokenizer::onWord() {
		readToken(WORD_REGEX, TOKEN_CLASS::WORD);
	}

	void RegexTokenizer::onSpace() {
		readToken(SPACE_REGEX, TOKEN_CLASS::SPACE);
	}

	void RegexTokenizer::onNewLine() {
		readToken(NEW_LINE_REGEX, TOKEN_CLASS::NEW_LINE);
	}

	void RegexTokenizer::onSingleLineComment() {
		readToken(SINGLELINE_COMMENT_REGEX, TOKEN_CLASS::SINGLELINE_COMMENT);
	}

	void RegexTokenizer::onMultiLineCommentStart() {
		readToken(MULTILINE_COMMENT_REGEX, TOKEN_CLASS::MULTILINE_COMMENT);
	}

	bool RegexTokenizer::checkForOperatorAndReact() {
		string op = "";
		if (OperatorTokenizeHelper::findOperator(op, *context)) {
			context->put(op, TOKEN_CLASS::OPERATOR);
			return true;
		}
		return false;
	}

	bool RegexTokenizer::checkForOtherSymbolsAndReact() {
		TOKEN_CLASS tokenClass;
		if (SymbolsTokenizeHelper::find(tokenClass, context->at(0))) {
			context->put(string(context->at(0), 1), tokenClass);
			return true;
		}
		return false;
	}

	void RegexTokenizer::readToken(const regex &reg, TOKEN_CLASS tokenClass) {
		const string& text = context->getText();
		std::smatch match;
		bool result = std::regex_search(text.cbegin() + context->textPosition(), text.cend(), match, reg);
		context->put(match[0], tokenClass);
	}
}