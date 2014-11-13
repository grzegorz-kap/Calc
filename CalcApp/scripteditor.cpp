#include "scripteditor.h"

ScriptEditor::ScriptEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionSave_as, SIGNAL(triggered()), this, SLOT(onSaveAsAction()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(onSaveAction()));
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
	QString scriptName = item->text();
	int N = ui.tabWidget->count();
	for (int i = 0; i < N; i++)
	{
		if (ui.tabWidget->tabText(i) == scriptName)
		{
			ui.tabWidget->setCurrentIndex(i);
			hide();
			show();
			return;
		}
	}
	addTab(ScriptEditWidget::getWorkingDirectory() + "/" + scriptName);
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