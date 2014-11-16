#include "CalcPlot\GraphDrawer.h"
#include <future>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
int main()
{
	auto graph = GraphDrawer::get();

	for (double i = 0.2; i <= 1; i++)
	{
		graph->plot(i);
		std::cout << i << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(1000));
	}

	system("pause");
	return 0;
}

