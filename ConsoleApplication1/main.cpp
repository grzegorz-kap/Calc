#include <iostream>
#include <string>
#include "Calc\Interpreter.h"

void main()
{
	PR::Interpreter inter;
	inter.workFromFile("dane.txt");
	system("pause");
}