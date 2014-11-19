#include "calcapp.h"

QFont CalcApp::font = QFont();


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
	interpreterConnector->connectToInterpreterSingals();
	
	QString temp = QDir::currentPath();
	interpreterConnector->workingDirectoryChanged(temp);
	fileWatcher.addPath(QDir::currentPath());
	ui.dirComboBox->workingDirectoryChanged(temp);
	scriptEditor.workingDirectoryChanged(temp);
	ui.variables->connectSlots();

	qRegisterMetaType<QString>("QString");
	qRegisterMetaType<std::string>("std::string");
	qRegisterMetaType<PR::VariableInfo>("PR::VariableInfo");

	
//	ui.commandL->setFocus();
	connect(ui.commandLine, SIGNAL(commandEntered(QString)), interpreterConnector, SLOT(commandToInterpreter(QString)));
	connect(ui.commandLine, SIGNAL(commandEntered(QString)), ui.console, SLOT(appendWithoutRealase(QString)));
	connect(ui.commandLine, SIGNAL(commandEntered(QString)), ui.commandHistory, SLOT(insertCommand(QString)));
	//connect(ui.commandHistory, SIGNAL(executeCommand(QString)), ui.console,(SLOT(appendWithoutRealase(QString))));
	connect(ui.commandHistory, SIGNAL(executeCommand(QString)), ui.commandLine, SLOT(appendPlainText(QString)));
	connect(ui.commandHistory, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), ui.commandHistory, SLOT(onItemDoubleClicked(QTreeWidgetItem *, int)));
	connect(interpreterConnector, SIGNAL(interpreterResponded(QString)), ui.console, SLOT(append(QString)));
	connect(interpreterConnector, SIGNAL(interpreterRespondedHtml(QString)), ui.console, SLOT(insertHtml(QString)));
	connect(interpreterConnector, SIGNAL(interpreterError(QString)), ui.console, SLOT(insertHtml(QString)));
	connect(interpreterConnector, SIGNAL(interpreterResponded()), ui.commandLine, SLOT(interpreterRespond()));
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

	connect(&scriptEditor, SIGNAL(runCommand(QString)), interpreterConnector, SLOT(commandToInterpreter(QString)));
	connect(&scriptEditor, SIGNAL(runCommand(QString)), ui.console, SLOT(appendWithoutRealase(QString)));
	connect(&scriptEditor, SIGNAL(runCommand(QString)), ui.commandHistory, SLOT(insertCommand(QString)));


	variablesEditor.connectToInterpretSingals();
	connect(ui.variables, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), &variablesEditor, SLOT(onVariableSelection(QTableWidgetItem *)));
	connect(&variablesEditor, SIGNAL(variableInformationRequest(QString)), interpreterConnector, SLOT(getInformation(QString)));
	connect(interpreterConnector, SIGNAL(sendVariableInformation(PR::VariableInfo)), &variablesEditor, SLOT(receiveVariableInformation(PR::VariableInfo)));

	setupFont();
	setupToolbar();
}

CalcApp::~CalcApp()
{

}

void CalcApp::setupFont()
{
	font.setFamily("Courier");
	font.setStyleHint(QFont::Monospace);
	font.setFixedPitch(true);
	font.setPointSize(10);

	ui.console->setFont(font);
	ui.commandLine->setFont(font);
	ScriptEditWidget::defaultFont = font;
}

void CalcApp::setupToolbar()
{
	QPushButton* button = new QPushButton(this);
	button->setIcon(QIcon(":/CalcApp/new.png"));
	button->setToolTip("New script");
	ui.mainToolBar->addWidget(button);
	connect(button, SIGNAL(clicked()), &scriptEditor, SLOT(onNewFileAction()));

	button = new QPushButton(this);
	button->setIcon(QIcon(":/CalcApp/stop.png"));
	button->setToolTip("Stop computing");
	ui.mainToolBar->addWidget(button);
	connect(button, SIGNAL(clicked()), this, SLOT(stopComputing()));
}

void CalcApp::stopComputing()
{
	PR::SignalEmitter::get()->call_stop();
}

void CalcApp::closeEvent(QCloseEvent *ev)
{
	scriptEditor.close();
	variablesEditor.close();
	ev->accept();
}

