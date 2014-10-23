#include "calcapp.h"

#include <qmetatype.h>


CalcApp::CalcApp(QWidget *parent)
	: QMainWindow(parent),
	interpreterConnector(new InterpreterConnector())
{
	ui.setupUi(this);
	
	//qRegisterMetaType<std::string>((const char *)"std::string");
	
	//QThread *t = new QThread();
	interpreterConnector = new InterpreterConnector();
	//t->start();
	
	ui.commandLine->setFocus();
	ui.splitter->setStretchFactor(1, 300);
	
	connect(ui.commandLine, SIGNAL(commandEntered(const std::string &)), interpreterConnector, SLOT(commandToInterpreter(const std::string &)));
	connect(interpreterConnector, SIGNAL(interpreterResponded(const QString&)), ui.console, SLOT(append(const QString&)));
	//interpreterConnector->moveToThread(t);
}

CalcApp::~CalcApp()
{

}

