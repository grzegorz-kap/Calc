#include "about.h"

About::About(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

About::~About()
{
}

void About::showAbout()
{
	ui.setupUi(this);
}