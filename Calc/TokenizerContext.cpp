#include "stdafx.h"
#include "TokenizerContext.h"

namespace KLab {
	TokenizerContext::TokenizerContext(string inputText) : text(inputText) {
		setupInitialState();
	}

	int TokenizerContext::textPosition() const {
		return text.Position();
	}

	bool TokenizerContext::isCharacterToProccess() {
		return text.isCharacterToProccess();
	}

	void TokenizerContext::put(unique_ptr<Token> &&token) {
		proccessBeforePut(*token);
		tokens.add(std::move(token));
	}

	string TokenizerContext::at(int offset, int length) {
		return text.at(offset, length);
	}

	char TokenizerContext::at(int offset /*= 0*/) {
		return text.at(offset);
	}

	void TokenizerContext::setupInitialState() {
		line = 1;
		column = 1;
	}

	void TokenizerContext::proccessBeforePut(Token &token) {
		text.incrementPosition(token.getLexemeLength());
		token.setLine(line);
		token.setColumn(column);
		updateColumnAndLine(token);
	}

	void TokenizerContext::updateColumnAndLine(const Token &token) {
		switch (token.getTokenClass()) {
		case TOKEN_CLASS::NEW_LINE:
			onNewLine(token.getLexemeLength());
			break;
		case TOKEN_CLASS::MULTILINE_COMMENT:
			onMultilineComment(token);
			break;
		default:
			column += token.getLexemeLength();
			break;
		}
	}

	void TokenizerContext::onNewLine(int tokenLength) {
		line += tokenLength;
		column = 1;
	}

	void TokenizerContext::onMultilineComment(const Token &token) {
		auto newLinesCount = std::count_if(token.cbegin(), token.cend(), [](char c){return c == '\n'; });
		if (newLinesCount > 0) {
			line += (int)newLinesCount;
			column = token.getLexemeLength() - token.lastIndexOf('\n');
		}
		else
			column += token.getLexemeLength();
	}

	bool TokenizerContext::isMultiLineCommentStart() {
		return text.at(0, 2, "%{");
	}

	bool TokenizerContext::isSingleLineCommentStart() {
		return text.at(0, '%') && !text.at(1, '{') || text.at(0, 2, "//");
	}

	bool TokenizerContext::isNewLineStart() {
		return text.at(0, '\n');
	}

	bool TokenizerContext::isSpaceStart() {
		return text.at(0, ' ') || text.at(0, '\t');
	}

	bool TokenizerContext::isWordStart() {
		return CharHelper::isLetter(text.at()) || text.at(0, '_');
	}

	bool TokenizerContext::isNumberStart() {
		return CharHelper::isDigit(text.at()) || text.at(0, '.') && CharHelper::isDigit(text.at(1));
	}
}