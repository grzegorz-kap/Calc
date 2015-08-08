#pragma once

#include <string>

using std::string;

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

	private:
		void initAfterTextSet();
	};
}
