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

	void TokenizerContext::addToken(unique_ptr<Token> &&token) {
		tokens->add(std::move(token));
	}

	const string& TokenizerContext::getText() const {
		return text.getText();
	}

	void TokenizerContext::setupInitialState() {
		line = 1;
		column = 1;
	}

	void TokenizerContext::incrementPosition(int value) {
		text.incrementPosition(value);
	}

	void TokenizerContext::setLine(int value) {
		line = value;
	}

	int TokenizerContext::getLine() const {
		return line;
	}

	void TokenizerContext::setColumn(int value) {
		column = value;
	}

	int TokenizerContext::getColumn() const {
		return column;
	}
}