#include "scripteditor.h"

int ScriptEditor::i = 0;

ScriptEditor::ScriptEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.actionNew->setShortcut(QKeySequence::New);
	ui.actionOtw_Rz->setShortcut(QKeySequence::Open);
	ui.actionSave->setShortcut(QKeySequence::Save);
	ui.actionSave_as->setShortcut(QKeySequence::SaveAs);
	ui.actionRun->setShortcut(QKeySequence::Refresh);


	connect(ui.actionSave_as, SIGNAL(triggered()), this, SLOT(onSaveAsAction()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(onSaveAction()));
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(onNewFileAction()));
	connect(ui.actionOtw_Rz, SIGNAL(triggered()), this, SLOT(onOpenAction()));
	connect(ui.actionRun, SIGNAL(triggered()), this, SLOT(onRunAction()));

	setupToolbar();
}

ScriptEditor::~ScriptEditor()
{

}


void ScriptEditor::addTab(QString pathArg)
{
	QString fileName = QDir(pathArg).dirName();
	ScriptEditWidget *widget = new ScriptEditWidget(ui.tabWidget);
	widget->setFilePath(pathArg);
	widget->readFromFile();
	connect(widget, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
	connect(widget, SIGNAL(fileSaved()), this, SLOT(onChangesSaved()));
	
	if (fileName == ".")
		fileName = "Untitled" + (i++ ? QString::number(i) : "") ;

	ui.tabWidget->addTab(widget, fileName);
	ui.tabWidget->setCurrentWidget(widget);
}

void ScriptEditor::onTextChanged()
{
	QObject *sender = QObject::sender();
	ScriptEditWidget *widget = dynamic_cast<ScriptEditWidget *>(sender);
	if (widget == nullptr)
		return;
	widget->setUpdated(true);
	int idx = ui.tabWidget->indexOf(widget);
	ui.tabWidget->setTabIcon(idx, QIcon(":/CalcApp/dot.png"));
}


void ScriptEditor::workingDirectoryChanged(QString newWorkingDirectory)
{
	ScriptEditWidget::setWorkingDirectory(newWorkingDirectory);
}

void ScriptEditor::onChangesSaved()
{
	ScriptEditWidget *widget = dynamic_cast<ScriptEditWidget *>(QObject::sender());
	if (widget == nullptr)
		return;
	ui.tabWidget->setTabIcon(ui.tabWidget->indexOf(widget), QIcon());
	ui.tabWidget->setTabText(ui.tabWidget->indexOf(widget), QDir(widget->getFilePath()).dirName());
}

void ScriptEditor::onScriptDblClicked(QListWidgetItem *item)
{
	QString scriptName = ScriptEditWidget::getWorkingDirectory() + "/" + item->text();
	int N = ui.tabWidget->count();
	for (int i = 0; i < N; i++)
	{
		ScriptEditWidget *widget = dynamic_cast<ScriptEditWidget*>(ui.tabWidget->widget(i));
		if (widget->getFilePath() == scriptName)
		{
			ui.tabWidget->setCurrentIndex(i);
			hide();
			show();
			return;
		}
	}
	addTab(scriptName);
	hide();
	show();
}

void ScriptEditor::onSaveAsAction()
{
	ScriptEditWidget *widget = dynamic_cast<ScriptEditWidget *>(ui.tabWidget->currentWidget());
	if (widget == nullptr)
		return;

	QString fileName = widget->askForPathToSave();
	if (fileName == "")
		return;
	widget->setUpdated(true);
	widget->setFilePath(fileName);
	widget->saveToFile();
}

void ScriptEditor::onSaveAction()
{
	ScriptEditWidget *widget = dynamic_cast<ScriptEditWidget *>(ui.tabWidget->currentWidget());
	if (widget == nullptr)
		return;
	widget->saveToFile();
}

void ScriptEditor::onNewFileAction()
{
	QString name = "Untitled" + (i++ == 0 ? "" : QString::number(i)) + ".m";
	addTab("");
	hide();
	show();
}


void ScriptEditor::onOpenAction()
{
	QStringList files = QFileDialog::getOpenFileNames(this, tr("Select scripts"),
		ScriptEditWidget::getWorkingDirectory(), tr("Script files (*.m)"));

	for (const auto &path : files)
	{
		int count = ui.tabWidget->count();
		bool found = false;
		i = 0;
		for (; i < count; i++)
		{
			ScriptEditWidget *widget = dynamic_cast<ScriptEditWidget*>(ui.tabWidget->widget(i));
			if (widget->getFilePath() == path)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			ui.tabWidget->setCurrentIndex(i);
			continue;
		}
		addTab(path);
	}
}

void ScriptEditor::onRunAction()
{
	ScriptEditWidget *widget = dynamic_cast<ScriptEditWidget*>(ui.tabWidget->currentWidget());
	widget->saveToFile();
	QString scriptName = QDir(widget->getFilePath()).dirName();
	scriptName = scriptName.left(scriptName.lastIndexOf("."));
	if (scriptName.size())
		emit runCommand(scriptName);
}

void ScriptEditor::setupToolbar()
{
	QPushButton* button = new QPushButton(this);
	button->setIcon(QIcon(":/CalcApp/new.png"));
	button->setToolTip("New script");
	ui.mainToolBar->addWidget(button);
	connect(button, SIGNAL(clicked()), this, SLOT(onNewFileAction()));

	button = new QPushButton(this);
	button->setIcon(QIcon(":/CalcApp/save.png"));
	button->setToolTip("Save");
	ui.mainToolBar->addWidget(button);
	connect(button, SIGNAL(clicked()), this, SLOT(onSaveAction()));


	button = new QPushButton(this);
	button->setIcon(QIcon(":/CalcApp/run.png"));
	button->setToolTip("Run script");
	ui.mainToolBar->addWidget(button);
	connect(button, SIGNAL(clicked()), this, SLOT(onRunAction()));
}