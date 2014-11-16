#pragma once

#include <discpp.h>
#include <cmath>
#include <thread>
#include <future>
#include <vector>

#include "exports.h"

using namespace std;

class CALCPLOT_API GraphDrawer
{
	GraphDrawer();
public:
	
	static GraphDrawer* get();
	void plot(double mult);
private:
	Dislin g;
	static GraphDrawer *inst;
	
	static void load();

	~GraphDrawer();
};

