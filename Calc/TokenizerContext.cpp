#include "stdafx.h"
#include "TokenizerContext.h"

namespace KLab {
	TokenizerContext::TokenizerContext(string inputText) : text(inputText) {
		tokens = shared_ptr<TokenList>(new TokenList());
		setupInitialState();
	}

	TokenizerContext::~TokenizerContext() {
	}

	int TokenizerContext::textPosition() const {
		return text.Position();
	}

	int TokenizerContext::textLength() const {
		return text.Length();
	}

	bool TokenizerContext::isCharacterToProccess() {
		return text.isCharacterToProccess();
	}

	void TokenizerContext::put(unique_ptr<Token> &&token) {
		proccessBeforePut(*token);
		tokens->add(std::move(token));
	}

	void TokenizerContext::put(const string &lexame, TOKEN_CLASS tokenClass) {
		put(unique_ptr<Token>(new Token(lexame, tokenClass)));
	}

	void TokenizerContext::put(string &&lexame, TOKEN_CLASS tokenClass) {
		put(unique_ptr<Token>(new Token(std::move(lexame), tokenClass)));
	}

	string TokenizerContext::at(int offset, int length) const {
		return text.at(offset, length);
	}

	char TokenizerContext::at(int offset /*= 0*/) const {
		return text.at(offset);
	}

	bool TokenizerContext::at(int offset, char character) const {
		return text.at(offset, character);
	}

	bool TokenizerContext::at(int offset, int length, const string &compare) const {
		return text.at(offset, length, compare);
	}

	shared_ptr<TokenList> TokenizerContext::getTokens() const {
		return tokens;
	}

	const string& TokenizerContext::getText() const {
		return text.getText();
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
}