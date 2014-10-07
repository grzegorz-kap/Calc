#include "calcapp.h"
#include <QtWidgets/QApplication>
#include "Calc\ComplexNumber.h"

int main(int argc, char *argv[])
{
	PR::ComplexNumber<float> aa;
	QApplication a(argc, argv);
	CalcApp w;
	w.show();
	return a.exec();
}
