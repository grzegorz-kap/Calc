#include "calcapp.h"

QFont CalcApp::font = QFont();

CalcApp::CalcApp(QWidget *parent)
	: QMainWindow(parent),
	interpreterConnector(new InterpreterConnector()),
	fileWatcher(AppData::docsAndSettings, this),
	variablesEditor(),
	scriptEditor()
{
	ui.setupUi(this);
	setWindowTitle("KLab 1.0");
	setWindowIcon(QIcon(":/CalcApp/Math.png"));

	interpreterConnector = new InterpreterConnector();
	interpreterConnector->connectStopComputing();
	variablesEditor.setInterpreter(interpreterConnector);

	QThread *t = new QThread();
	t->start();
	interpreterConnector->moveToThread(t);
	interpreterConnector->connectToInterpreterSingals();

	qRegisterMetaType<QString>("QString");
	qRegisterMetaType<std::string>("std::string");
	qRegisterMetaType<KLab::VariableInfo>("PR::VariableInfo");

	connect(ui.commandLine, SIGNAL(commandEntered(QString)), interpreterConnector, SLOT(commandToInterpreter(QString)));
	connect(ui.commandLine, SIGNAL(commandEntered(QString)), ui.console, SLOT(appendWithoutRealase(QString)));
	connect(ui.commandLine, SIGNAL(commandEntered(QString)), ui.commandHistory, SLOT(insertCommand(QString)));
	connect(ui.commandHistory, SIGNAL(executeCommand(QString)), ui.commandLine, SLOT(appendPlainText(QString)));
	connect(ui.commandHistory, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), ui.commandHistory, SLOT(onItemDoubleClicked(QTreeWidgetItem *, int)));
	connect(interpreterConnector, SIGNAL(interpreterResponded(QString)), ui.console, SLOT(append(QString)));
	connect(interpreterConnector, SIGNAL(interpreterRespondedHtml(QString)), ui.console, SLOT(insertHtml(QString)));
	connect(interpreterConnector, SIGNAL(interpreterError(QString)), ui.console, SLOT(insertHtml(QString)));
	connect(interpreterConnector, SIGNAL(interpreterResponded()), ui.commandLine, SLOT(interpreterRespond()));
	connect(&fileWatcher, SIGNAL(directoryChanged(QString)), &fileWatcher, SLOT(changed(QString)));
	connect(interpreterConnector, SIGNAL(interpreterResponded()), &variablesEditor, SLOT(computationComplate()));
	connect(interpreterConnector, SIGNAL(executionStarted()), ui.commandLine, SLOT(executionStarted()));
	connect(&fileWatcher, SIGNAL(sendFileList(QStringList)), ui.filesList, SLOT(set(QStringList)));
	connect(&fileWatcher, SIGNAL(fileUpdated(QString)), interpreterConnector, SLOT(updateFile(QString)));
	connect(ui.workingDirChangeButton, SIGNAL(clicked()), &fileWatcher, SLOT(fileDialogButtonClicked()));
	connect(&fileWatcher, SIGNAL(workingDirectoryChanged(QString)), interpreterConnector, SLOT(workingDirectoryChanged(QString)));
	connect(&fileWatcher, SIGNAL(workingDirectoryChanged(QString)), ui.dirComboBox, SLOT(workingDirectoryChanged(QString)));
	connect(&fileWatcher, SIGNAL(workingDirectoryChanged(QString)), &scriptEditor, SLOT(workingDirectoryChanged(QString)));
	connect(ui.dirComboBox, SIGNAL(currentIndexChanged(QString)), &fileWatcher, SLOT(setNewDirectory(QString)));
	connect(ui.filesList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), &scriptEditor, SLOT(onScriptDblClicked(QListWidgetItem*)));
	connect(interpreterConnector, SIGNAL(clsScreen()), ui.console, SLOT(clear()));
	fileWatcher.changed(AppData::docsAndSettings);

	connect(&scriptEditor, SIGNAL(runCommand(QString)), interpreterConnector, SLOT(commandToInterpreter(QString)));
	connect(&scriptEditor, SIGNAL(runCommand(QString)), ui.console, SLOT(appendWithoutRealase(QString)));
	connect(&scriptEditor, SIGNAL(runCommand(QString)), ui.commandHistory, SLOT(insertCommand(QString)));

	variablesEditor.connectToInterpretSingals();
	connect(ui.variables, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), &variablesEditor, SLOT(onVariableSelection(QTableWidgetItem *)));
	connect(&variablesEditor, SIGNAL(variableInformationRequest(QString)), interpreterConnector, SLOT(getInformation(QString)));
	connect(interpreterConnector, SIGNAL(sendVariableInformation(KLab::VariableInfo)), &variablesEditor, SLOT(receiveVariableInformation(KLab::VariableInfo)));

	setupFont();
	setupToolbar();

	AppData::createCalcFolder();
	QString temp = AppData::docsAndSettings;
	interpreterConnector->workingDirectoryChanged(temp);
	fileWatcher.addPath(temp);
	ui.dirComboBox->workingDirectoryChanged(temp);
	scriptEditor.workingDirectoryChanged(temp);
	ui.variables->connectSlots();

	connect(ui.actionNew_script, SIGNAL(triggered()), &scriptEditor, SLOT(onNewFileAction()));
	connect(ui.actionAbout_program, SIGNAL(triggered()), this, SLOT(onAboutAction()));
}

CalcApp::~CalcApp()
{
}

void CalcApp::onAboutAction()
{
	QDialog *about = new QDialog(this);
	Ui_About aboutUi;
	aboutUi.setupUi(about);
	about->show();
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
	KLab::SignalEmitter::get()->call_stop();
}

void CalcApp::closeEvent(QCloseEvent *ev)
{
	if (scriptEditor.close() && variablesEditor.close())
		ev->accept();
	else
		ev->ignore();
}