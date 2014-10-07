#include "calcapp.h"

CalcApp::CalcApp(QWidget *parent)
	: QMainWindow(parent),
	interpreterConnector(this)
{
	ui.setupUi(this);

	connect(ui.commandLine, SIGNAL(commandEntered(std::string)), &interpreterConnector, SLOT(commandToInterpreter(std::string)));
	connect(&interpreterConnector, SIGNAL(interpreterResponded(const QString&)), ui.console, SLOT(setText(const QString&)));
}

CalcApp::~CalcApp()
{

}

