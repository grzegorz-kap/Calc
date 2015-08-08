#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include "ui_about.h"

class About : public QWidget
{
	Q_OBJECT

public:
	About(QWidget *parent = 0);
	~About();
	void showAbout();

private:
	Ui::About ui;
};

#endif // ABOUT_H
