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
	
	g.gaxpar(*std::min_element(x,x+x_count),*std::max_element(x,x+x_count), 
		"EXTEND", "X", &x_min_limit, &x_max_limit, &x_first_axis_label, &x_step_axis_label, &x_ndig);

	g.gaxpar(*std::min_element(y, y + y_count), *std::max_element(y, y + y_count),
		"EXTEND", "Y", &y_min_limit, &y_max_limit, &y_first_axis_label, &y_step_axis_label, &y_ndig);

	g.graf(x_min_limit,x_max_limit,x_first_axis_label,x_step_axis_label,
		y_min_limit,y_max_limit,y_first_axis_label,y_step_axis_label);

	g.setrgb(0.7, 0.7, 0.7);
	g.grid(1, 1);

	g.color("fore");
	g.height(50);
	g.title();
	
	g.color("red");
	g.curve(x, y, x_count);
	g.disfin();

}
