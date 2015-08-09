#pragma once

#include "commons.h"

namespace KLab {
	class TokenizedText {
	private:
		string text;
		unsigned int position;
		unsigned int length;
	public:
		TokenizedText(const string &text);
		TokenizedText(string &&text);
		~TokenizedText();

		char at(int offset = 0) const;
		string at(int offset, int length) const;
		bool at(int offset, char compareTo) const;
		bool at(int offset, int length, const string &compareTo) const;
		bool isCharacterToProccess() const;
		void incrementPosition(int value);

		unsigned int Position() const;
		void Position(unsigned int val);
		unsigned int Length() const;
		void Length(unsigned int val);
		const string& getText() const;

	private:
		void initAfterTextSet();
	};
}
