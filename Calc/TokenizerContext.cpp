#include "stdafx.h"
#include "TokenizerContext.h"

namespace KLab {
	TokenizerContext::TokenizerContext(const string& inputText) {
		text = inputText;
		init();
	}

	TokenizerContext::TokenizerContext(string &&inputText) {
		text = std::move(inputText);
		init();
	}

	TokenizerContext::~TokenizerContext() {
	}

	void TokenizerContext::init() {
		index = 0;
		length = text.size();
	}

	char TokenizerContext::at(int offset) const {
		int currentIndex = index + offset;
		return currentIndex >= 0 && currentIndex < length ? text[currentIndex] : '\0';
	}

	char TokenizerContext::last() const {
		return length > 0 ? *(text.end() - 1) : '\0';
	}

	bool TokenizerContext::EoI() const {
		return index >= length;
	}

	void TokenizerContext::increment(int value) {
		index += value;
	}

	void TokenizerContext::decrementLength(int value) {
		length -= value;
	}

	string& TokenizerContext::getTextRef() {
		return text;
	}

	int TokenizerContext::getIndex() const {
		return index;
	}

	int TokenizerContext::getLength() const {
		return length;
	}
}