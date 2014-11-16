#pragma once

#include <discpp.h>
#include <cmath>
#include <thread>
#include <future>
#include <vector>

using namespace std;

class  GraphDrawer
{
	
public:
	GraphDrawer();
	~GraphDrawer();
	void plot(double *x,double *y,int x_count,int y_count);
	void plot3(double *x,double *y,double *z, int x_n,int y_n,int z_n);
private:

	void setupXAxisParameters(double *x, int n);
	void setupYAxisParameters(double *y, int n);
	void setupZAxisParameters(double *z, int n);

	Dislin g;
	double x_min_limit;
	double x_max_limit;
	double x_first_axis_label;
	double x_step_axis_label;
	int x_ndig;
	
	double y_min_limit;
	double y_max_limit;
	double y_first_axis_label;
	double y_step_axis_label;
	int y_ndig;
	
	double z_min_limit;
	double z_max_limit;
	double z_first_axis_label;
	double z_step_axis_label;
	int z_ndig;

};

