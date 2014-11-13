#include "calcapp.h"




CalcApp::CalcApp(QWidget *parent)
	: QMainWindow(parent),
	interpreterConnector(new InterpreterConnector()),
	fileWatcher(QDir::currentPath(), this),
	variablesEditor(),
	scriptEditor()
{
	ui.setupUi(this);
	interpreterConnector = new InterpreterConnector();
	interpreterConnector->connectStopComputing();
	variablesEditor.setInterpreter(interpreterConnector);
	
	QThread *t = new QThread();
	t->start();
	interpreterConnector->moveToThread(t);
	
	QString temp = QDir::currentPath();
	interpreterConnector->workingDirectoryChanged(temp);
	fileWatcher.addPath(QDir::currentPath());
	ui.dirComboBox->workingDirectoryChanged(temp);
	scriptEditor.workingDirectoryChanged(temp);


	PR::SignalEmitter::get()->connect_output(boost::bind(&InterpreterConnector::signal_receiver, interpreterConnector, _1, _2));
	PR::SignalEmitter::get()->connect_errors(boost::bind(&InterpreterConnector::errors_receiver, interpreterConnector, _1, _2));

	ui.variables->connectSlots();

	qRegisterMetaType<QString>("QString");
	qRegisterMetaType<std::string>("std::string");
	qRegisterMetaType<PR::VariableInfo>("PR::VariableInfo");

	
//	ui.commandL->setFocus();
	connect(ui.commandLine, SIGNAL(commandEntered(QString)), interpreterConnector, SLOT(commandToInterpreter(QString)));
	connect(ui.commandLine, SIGNAL(commandEntered(QString)), ui.console, SLOT(appendWithoutRealase(QString)));
	connect(ui.commandLine, SIGNAL(commandEntered(QString)), ui.commandHistory, SLOT(insertCommand(QString)));
	connect(ui.commandHistory, SIGNAL(executeCommand(QString)), ui.console,(SLOT(appendWithoutRealase(QString))));
	connect(ui.commandHistory, SIGNAL(executeCommand(QString)), interpreterConnector, SLOT(commandToInterpreter(QString)));
	connect(ui.commandHistory, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), ui.commandHistory, SLOT(onItemDoubleClicked(QTreeWidgetItem *, int)));
	connect(interpreterConnector, SIGNAL(interpreterResponded(QString)), ui.console, SLOT(append(QString)));
	connect(interpreterConnector, SIGNAL(interpreterRespondedHtml(QString)), ui.console, SLOT(insertHtml(QString)));
	connect(interpreterConnector, SIGNAL(interpreterError(QString)), ui.console, SLOT(insertHtml(QString)));
	connect(&fileWatcher, SIGNAL(directoryChanged(QString)), &fileWatcher, SLOT(changed(QString)));
	connect(&fileWatcher, SIGNAL(sendFileList(QStringList)), ui.filesList, SLOT(set(QStringList)));
	connect(&fileWatcher, SIGNAL(fileUpdated(QString)), interpreterConnector, SLOT(updateFile(QString)));
	connect(ui.workingDirChangeButton, SIGNAL(clicked()), &fileWatcher, SLOT(fileDialogButtonClicked()));
	connect(&fileWatcher, SIGNAL(workingDirectoryChanged(QString)), interpreterConnector, SLOT(workingDirectoryChanged(QString)));
	connect(&fileWatcher, SIGNAL(workingDirectoryChanged(QString)), ui.dirComboBox, SLOT(workingDirectoryChanged(QString)));
	connect(&fileWatcher, SIGNAL(workingDirectoryChanged(QString)), &scriptEditor, SLOT(workingDirectoryChanged(QString)));
	connect(ui.dirComboBox, SIGNAL(currentIndexChanged(QString)), &fileWatcher, SLOT(setNewDirectory(QString)));
	connect(ui.filesList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), &scriptEditor, SLOT(onScriptDblClicked(QListWidgetItem*)));
	fileWatcher.changed(QDir::currentPath());


	variablesEditor.connectToInterpretSingals();
	connect(ui.variables, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), &variablesEditor, SLOT(onVariableSelection(QTableWidgetItem *)));
	connect(&variablesEditor, SIGNAL(variableInformationRequest(QString)), interpreterConnector, SLOT(getInformation(QString)));
	connect(interpreterConnector, SIGNAL(sendVariableInformation(PR::VariableInfo)), &variablesEditor, SLOT(receiveVariableInformation(PR::VariableInfo)));
}

CalcApp::~CalcApp()
{

}

void CalcApp::closeEvent(QCloseEvent *ev)
{
	scriptEditor.close();
	variablesEditor.close();
	ev->accept();
}

