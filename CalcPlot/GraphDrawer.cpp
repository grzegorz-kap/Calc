#include "stdafx.h"
#include "GraphDrawer.h"

GraphDrawer* GraphDrawer::inst = nullptr;

GraphDrawer::GraphDrawer()
{
	

	
}


GraphDrawer::~GraphDrawer()
{
}

GraphDrawer* GraphDrawer::get()
{
	load();
	return inst;
}

void GraphDrawer::load()
{
	if (inst == nullptr)
		inst = new GraphDrawer();
}

void GraphDrawer::plot(double mult)
{
	int n = 100, i, ic;
	double fpi = 3.1415926 / 180.0, step, x;
	double xray[100], y1ray[100], y2ray[100];
	g.erase();
	step = 360. / (n - 1);


	for (i = 0; i < n; i++)
	{
		xray[i] = i * step;
		x = xray[i] * fpi;
		y1ray[i] = sin(x)*mult;
		y2ray[i] = cos(x)/mult;
	}

	
	g.window(100, 100, 800, 640);
	g.metafl("cons");
	g.scrmod("revers");
	g.disini();
	
	g.name("X-axis", "x");
	g.name("Y-axis", "y");

	g.labdig(-1, "x");
	g.ticks(9, "x");
	g.ticks(10, "y");

	g.titlin("Demonstration of CURVE", 1);
	g.titlin("SIN(X), COS(X)", 3);

	ic = g.intrgb(0.95, 0.95, 0.95);
	g.axsbgd(ic);

	g.graf(0.0, 360.0, 0.0, 90.0, -10.0, 10.0, -10.0, 2.0);
	g.setrgb(0.7, 0.7, 0.7);
	g.grid(1, 1);

	g.color("fore");
	g.height(50);
	g.title();
	
	g.color("red");
	g.curve(xray, y1ray, n);
	g.color("green");
	g.curve(xray, y2ray, n);
	g.disfin();

	
}
