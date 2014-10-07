#include "stdafx.h"
#include "NumberReader.h"

namespace PR
{
	unsigned int NumberReader::read(const string &input, string &output, int start_p)
	{
		NumberReader numberReader(input, output, start_p);
		numberReader.readDigits();
		numberReader.fractionalPart();
		numberReader.ePart();
		numberReader.readI();
		return output.size();
	}

	NumberReader::NumberReader(const string &in, string &out, int position)
		:in(in), out(out), position(position)
	{
		out = "";
		N = in.size();
		exp = false;
	}

	NumberReader::~NumberReader()
	{
	}

	void NumberReader::readDigits()
	{
		while (position < N && TokenizerHelper::isDigit(in[position]))
			out += in[position++];
	}

	void NumberReader::fractionalPart()
	{
		if (position<N-1&&in[position] == '.'&&TokenizerHelper::isDigit(in[position+1]))
		{
			position++;
			out.append(".");
			readDigits();
			if (out.back() == '.')
				throw PR::CalcException("Number read error!", position - 1);
		}
	}

	void NumberReader::ePart()
	{
		bool error = false;
		if (position < N && (in[position] == 'e' || in[position] == 'E'))
		{
			out += in[position++];
			if (position == N)
				error = true;
			if (in[position] == '-' || in[position] == '+')
				out += in[position++];
			readDigits();

			if (!TokenizerHelper::isDigit(out.back()) || error)
				throw PR::CalcException("Number read error!", position - 1);

			exp = true;
		}
	}

	void NumberReader::readI()
	{
		if (position < N&&in[position] == 'i')
		{
			if (exp)
				throw PR::CalcException("Number read error!", position - 1);
			else
				out.append("i");
		}
	}
}