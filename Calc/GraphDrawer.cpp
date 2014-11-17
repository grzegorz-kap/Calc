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

	ic = g.intrgb(0.95, 0.95, 0.95);
	g.axsbgd(ic);
	
	setupXAxisParameters(x, x_count);
	setupYAxisParameters(y, y_count);

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

void GraphDrawer::plot3(double *x, double *y, double *z, int x_n, int y_n, int z_n)
{
	int ic;
	g.erase();
	
	g.window(100, 100, 800, 640);
	g.metafl("cons");
	g.scrmod("revers");
	g.disini();

	g.name("X-axis", "x");
	g.name("Y-axis", "y");
	g.name("Z-axis", "z");

	g.labdig(-1, "x");
	g.ticks(9, "x");
	g.ticks(10, "y");
	g.ticks(9, "z");

	g.view3d(-1, -1, .3, "ABS");

	ic = g.intrgb(0.95, 0.95, 0.95);
	g.axsbgd(ic);

	//g.axis3d(800, 640, 500);

	setupXAxisParameters(x, x_n);
	setupYAxisParameters(y, y_n);
	setupZAxisParameters(z, z_n);

	g.graf3d(x_min_limit, x_max_limit, x_first_axis_label, x_step_axis_label,
		y_min_limit, y_max_limit, y_first_axis_label, y_step_axis_label,
		z_min_limit,z_max_limit,z_first_axis_label,z_step_axis_label);

	g.height(50);
	g.setrgb(0.7, 0.7, 0.7);
	g.grid3d(1, 1, "ALL");

	g.color("red");
	g.curv3d(x, y, z, x_n);
	g.disfin();
}

void GraphDrawer::setupXAxisParameters(double *x,int n)
{
	g.gaxpar(*std::min_element(x, x + n), *std::max_element(x, x + n),
		"EXTEND", "X", &x_min_limit, &x_max_limit, &x_first_axis_label, &x_step_axis_label, &x_ndig);
}

void GraphDrawer::setupYAxisParameters(double *y, int n)
{
	g.gaxpar(*std::min_element(y, y + n), *std::max_element(y, y + n),
		"EXTEND", "Y", &y_min_limit, &y_max_limit, &y_first_axis_label, &y_step_axis_label, &y_ndig);
}

void GraphDrawer::setupZAxisParameters(double *z, int n)
{
	g.gaxpar(*std::min_element(z, z + n), *std::max_element(z, z  + n),
		"EXTEND", "Z", &z_min_limit, &z_max_limit, &z_first_axis_label, &z_step_axis_label, &z_ndig);
}

void GraphDrawer::surface(double *x, double *y, double *z, size sx, size sy, size sz)
{
	int ic;
	g.erase();

	g.window(100, 100, 800, 640);
	g.metafl("cons");
	g.scrmod("revers");
	g.disini();

	g.name("X-axis", "x");
	g.name("Y-axis", "y");
	g.name("Z-axis", "z");

	g.labdig(-1, "x");
	g.ticks(9, "x");
	g.ticks(10, "y");
	g.ticks(9, "z");

	g.view3d(-1, -1, .3, "ABS");

	ic = g.intrgb(0.95, 0.95, 0.95);
	g.axsbgd(ic);

	//g.axis3d(800, 640, 500);

	setupXAxisParameters(x, sx.n);
	setupYAxisParameters(y, sy.n);
	setupZAxisParameters(z, sz.m*sz.n);

	g.graf3d(x_min_limit, x_max_limit, x_first_axis_label, x_step_axis_label,
		y_min_limit, y_max_limit, y_first_axis_label, y_step_axis_label,
		z_min_limit, z_max_limit, z_first_axis_label, z_step_axis_label);

	g.height(50);
	g.setrgb(0.7, 0.7, 0.7);
	g.grid3d(1, 1, "ALL");

	g.color("green");
	g.surmat(z, sz.m, sz.n, 1, 1);
	g.disfin();
}