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

		char at(int offset = 0);
		string at(int offset, int length);
		bool at(int offset, char compareTo);
		bool at(int offset, int length, string compareTo);
		bool isCharacterToProccess();
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
