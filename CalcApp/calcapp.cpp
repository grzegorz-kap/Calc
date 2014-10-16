#include "calcapp.h"

#include <qmetatype.h>


CalcApp::CalcApp(QWidget *parent)
	: QMainWindow(parent),
	interpreterConnector(new InterpreterConnector())
{
	ui.setupUi(this);
	
	qRegisterMetaType<std::string>((const char *)"std::string");
	
	QThread *t = new QThread();
	interpreterConnector = new InterpreterConnector();
	t->start();

	connect(ui.commandLine, SIGNAL(commandEntered(std::string)), interpreterConnector, SLOT(commandToInterpreter(std::string)));
	connect(interpreterConnector, SIGNAL(interpreterResponded(const QString&)), ui.console, SLOT(setText(const QString&)));
	interpreterConnector->moveToThread(t);
}

CalcApp::~CalcApp()
{

}

