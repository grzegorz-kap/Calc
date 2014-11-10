#include "variableseditor.h"

VariablesEditor::VariablesEditor(InterpreterConnector *interpreter,QWidget *parent)
	: QWidget(parent)
{
	interpreterConnector = interpreter;
	ui.setupUi(this);
	setWindowFlags(Qt::Window);
}

VariablesEditor::~VariablesEditor()
{

}

void VariablesEditor::onVariableSelection(QTableWidgetItem *item)
{
	if (item == nullptr || item->column() != 0)
		return;
	emit variableInformationRequest(item->text());
}

void VariablesEditor::receiveVariableInformation(PR::VariableInfo info)
{
	auto tabs = ui.tabWidget;
	
	QWidget *widget = findTab(info.getName().c_str());
	int idx;
	if (widget == nullptr)
	{
		widget = new VariableEditWidget(ui.tabWidget);
		ui.tabWidget->addTab(widget, info.getName().c_str());
		connect(widget, SIGNAL(notifyVariableUpdate(QString)), interpreterConnector, SLOT(commandToInterpreter(QString)));
	}

	idx = ui.tabWidget->indexOf(widget);
	ui.tabWidget->setCurrentIndex(idx);
	show();
	
	dynamic_cast<VariableEditWidget *>(widget)->loadWidget(info);
}

QWidget* VariablesEditor::findTab(const QString &name)
{
	int tabs_number = ui.tabWidget->count();
	for (int i=0; i < tabs_number; i++)
	{
		if (ui.tabWidget->tabText(i) == name)
			return ui.tabWidget->widget(i);
	}

	return nullptr;
}