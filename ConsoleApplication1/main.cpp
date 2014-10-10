#include <iostream>

#include "Calc\Interpreter.h"



void main()
{
	PR::Interpreter interpreter;
	std::cout << interpreter.workFromFile("dane.txt");

	std::cout << std::endl;
	system("pause");
}