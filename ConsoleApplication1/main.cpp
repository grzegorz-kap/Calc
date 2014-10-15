#include <iostream>

#include "Calc\Interpreter.h"



void main()
{
	PR::Interpreter interpreter;
	interpreter.workFromFile("dane.txt");

	std::cout << std::endl;
	system("pause");
}