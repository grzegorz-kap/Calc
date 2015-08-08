#pragma once

#include <string>

#include "CalcException.h"
#include "TokenizerHelper.h"

using std::string;

namespace KLab
{
	class NumberReader
	{
	public:
		/**
		Function reads complex number from string
		@input - Reference to input string
		@output - Reference to output string with number
		@start_p - Starting position in input string
		Returns number or readed characters.
		*/
		static string read(const string &input, int start_p = 0);

	private:
		string out;
		NumberReader(const string &refIn, int start_p);
		~NumberReader();

		void readDigits();
		void fractionalPart();
		void ePart();
		void readI();

		const string &in;
		int position;
		int N;
		bool exp;
	};
}
