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
	
public:
	GraphDrawer();
	~GraphDrawer();
	void plot(double *x,double *y,int x_count,int y_count);
private:
	Dislin g;
};

