#include "variableseditor.h"

VariablesEditor::VariablesEditor(QWidget *parent)
	: QWidget(parent)
{
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
	
	QString variableName = item->text();

	ui.tabWidget->addTab(new VariableEditWidget(ui.tabWidget), variableName);

	show();

}
