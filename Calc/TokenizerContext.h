#pragma once

#include <string>

using std::string;

namespace KLab {
	class TokenizerContext {
	private:
		string text;
		int length;
		int index;

	public:
		TokenizerContext(const string& inputText);
		TokenizerContext(string &&inputText);
		~TokenizerContext();
		char at(int index) const;
		char last() const;
		bool EoI() const;
		void increment(int value);
		void decrementLength(int value);
		string& getTextRef();
		int getIndex() const;
		int getLength() const;

	private:
		void init();
	};
}
