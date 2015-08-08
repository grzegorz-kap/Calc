#include "stdafx.h"
#include "TokenizedText.h"

namespace KLab {
	TokenizedText::TokenizedText(const string &text) {
		this->text = text;
		initAfterTextSet();
	}

	TokenizedText::TokenizedText(string &&text) {
		this->text = std::move(text);
		initAfterTextSet();
	}

	TokenizedText::~TokenizedText() {
	}

	char TokenizedText::at(int offset /*= 0*/) {
		return offset + position < length && offset + position >= 0 ? text[position + offset] : '\0';
	}

	string TokenizedText::at(int offset, int length) {
		return (position + offset + length > this->length) ? ("") : text.substr(position + offset, length);
	}

	bool TokenizedText::at(int offset, char compareTo) {
		return at(offset) == compareTo;
	}

	bool TokenizedText::at(int offset, int length, string compareTo) {
		return at(offset, length) == compareTo;
	}

	void TokenizedText::initAfterTextSet() {
		position = 0;
		length = static_cast<int>(text.length());
	}

	bool TokenizedText::isCharacterToProccess() {
		return position < length;
	}

	void TokenizedText::incrementPosition(int value) {
		position += value;
	}

	unsigned int TokenizedText::Position() const {
		return position;
	}

	void TokenizedText::Position(unsigned int val) {
		position = val;
	}

	unsigned int TokenizedText::Length() const {
		return length;
	}

	void TokenizedText::Length(unsigned int val) {
		length = val;
	}

	const string& TokenizedText::getText() const {
		return text;
	}
}