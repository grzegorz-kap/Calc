#ifndef CALCAPP_H
#define CALCAPP_H

#include <QtWidgets/QMainWindow>
#include <qthread.h>


#include "ui_calcapp.h"
#include "interpreterconnector.h"


class CalcApp : public QMainWindow
{
	Q_OBJECT

public:
	CalcApp(QWidget *parent = 0);
	~CalcApp();

private:
	Ui::CalcAppClass ui;
	InterpreterConnector *interpreterConnector;
	

};

#endif // CALCAPP_H
