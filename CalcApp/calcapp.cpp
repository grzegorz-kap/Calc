#include "calcapp.h"

#include <qmetatype.h>


CalcApp::CalcApp(QWidget *parent)
	: QMainWindow(parent),
	interpreterConnector(new InterpreterConnector())
{
	ui.setupUi(this);
	interpreterConnector = new InterpreterConnector();
	QThread *t = new QThread();
	interpreterConnector->moveToThread(t);
	t->start();

	PR::SignalEmitter::get()->connect_output(boost::bind(&InterpreterConnector::signal_receiver, interpreterConnector, _1, _2));
	PR::SignalEmitter::get()->connect_errors(boost::bind(&InterpreterConnector::errors_receiver, interpreterConnector, _1, _2));

	qRegisterMetaType<QString>("QString");
	qRegisterMetaType<std::string>("std::string");
	
	ui.commandLine->setFocus();
	ui.splitter->setStretchFactor(1, 300);
	
	connect(ui.commandLine, SIGNAL(commandEntered(const std::string &)), interpreterConnector, SLOT(commandToInterpreter(const std::string &)));
	connect(ui.commandLine, SIGNAL(commandEntered(const QString &)), ui.console, SLOT(appendWithoutRealase(const QString &)));
	connect(interpreterConnector, SIGNAL(interpreterResponded(const QString&)), ui.console, SLOT(append(const QString&)));
	connect(interpreterConnector, SIGNAL(interpreterError(const QString &)), ui.console, SLOT(insertHtml(const QString&)));

}

CalcApp::~CalcApp()
{

}

