#pragma once

#include <string>

#include "CalcException.h"
#include "TokenizerHelper.h"

using std::string;

namespace PR
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
		static unsigned int read(const string &input, string &output, int start_p = 0);

	private:

		NumberReader(const string &refIn, string &refOut, int start_p);
		~NumberReader();

		void readDigits();
		void fractionalPart();
		void ePart();
		void readI();

		const string &in;
		string &out;
		int position;
		int N;
		bool exp;
	};

}
