#pragma once

#include <string>
using std::string;
namespace PR
{
	class NumericException
	{
		std::string message;
		NumericException(std::string &&message);
	public:
		~NumericException();

		static void throwMatrixMultDimensions();
		static void throwLogarithmFromZero();
		static void throwLogarithmZeroBase();
	};

}
