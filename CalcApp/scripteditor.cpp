#include "scripteditor.h"

ScriptEditor::ScriptEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	addTab("C:/files/plik.m");
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
	ui.tabWidget->addTab(widget, fileName);
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