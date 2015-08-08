#pragma once

#include <discpp.h>
#include <cmath>
#include <thread>
#include <future>
#include <vector>

using namespace std;

//! Struktura przechowuje wymiary macierzy.
struct size
{
	//! Konstruktor ustawiaj¹cy pola struktury.
	//! \param i to liczba wierszy.
	//! \param j to liczba kolumn.
	size(int i, int j) :m(i), n(j){}
	int m; //!< Przechowuje liczbe wierszy.
	int n; //!< Przechowuje liczbe kolumn.
};

//! Klasa rysujaca wykresy 2D i 3D.
class  GraphDrawer
{
public:

	//! Domyslny konstruktor
	GraphDrawer();
	~GraphDrawer();

	//! Metoda rysuje liniowy wykres dwuwymiarowy.
	//! \param x  tablica wspolrzednych osi x.
	//! \param y  tablica wspolrzednych osi y.
	//! \param x_count  rozmiar tablicy x.
	//! \param y_count  rozmiar tablicy y.
	void plot(double *x, double *y, int x_count, int y_count);

	//! Metoda rysuje liniowy wykres 3d.
	//! \param x tablica wspolrzednych x.
	//! \param y tablica wspolrzednych y.
	//! \param z tablica wspolrzednych z.
	//! \param x_n rozmiar tablicy x.
	//! \param y_n rozmiar tablicy y.
	//! \param z_n rozmiar tablicy z.
	void plot3(double *x, double *y, double *z, int x_n, int y_n, int z_n);

	//! Rysuje powierzchnie 3d.
	//! \param x tablica wspolrzednych x.
	//! \param y tablica wspolrzednych y.
	//! \param z tablica wspolrzednych z.
	void surface(double *x, double *y, double *z, size sx, size sy, size sz);
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
