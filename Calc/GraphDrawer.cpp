#include "stdafx.h"
#include "GraphDrawer.h"


GraphDrawer::GraphDrawer()
{	
}


GraphDrawer::~GraphDrawer()
{
}

void GraphDrawer::plot(double *x , double *y, int x_count,int y_count)
{
	int ic;
	g.erase();
	
	if (x_count != y_count)
		throw 'c';
	
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
	g.curve(x, y, x_count);
	g.disfin();

}
