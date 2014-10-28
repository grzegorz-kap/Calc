#pragma once

#include "CalcException.h"

#include <string>
using std::string;
namespace PR
{
	class NumericException
		: public CalcException
	{
		//std::string message;
		NumericException(std::string &&message);
	public:
		~NumericException();

		static void throwMatrixMultDimensions();
		static void throwLogarithmFromZero();
		static void throwLogarithmZeroBase();
		static void throwMatrixLogDimensions();
		static void throwLuNotSquare();
	};

}
