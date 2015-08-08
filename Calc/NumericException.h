#pragma once

#include "CalcException.h"

#include <string>
using std::string;
namespace KLab
{
	class NumericException
		: public CalcException
	{
		//std::string message;

	public:
		NumericException(std::string &&message);
		~NumericException();

		static void throwMatrixMultDimensions();
		static void throwLogarithmFromZero();
		static void throwLogarithmZeroBase();
		static void throwMatrixLogDimensions();
		static void throwLuNotSquare();
		static void throwIndexMustBeReal();
		static void throwIndexOutOfRange();
	};
}
