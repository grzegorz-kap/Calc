#include "variableseditor.h"

VariablesEditor::VariablesEditor(QWidget *parent)
	: QWidget(parent)
{

	ui.setupUi(this);
	setWindowFlags(Qt::Window);
	setWindowTitle("Variables editor");
	setWindowIcon(QIcon(":/CalcApp/Matrix-icon.png"));
	ui.tabWidget->setTabsClosable(true);
	connect(ui.tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onCurrentTabChanged(int)));
	connect(ui.tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabClose(int)));
}

VariablesEditor::~VariablesEditor()
{

}

void VariablesEditor::connectToInterpretSingals()
{
	PR::SignalEmitter::get()->connect_updated_variables_slot(boost::bind(&VariablesEditor::receiveVarsUpdate, this, _1, _2));
	PR::SignalEmitter::get()->connect_removed_variables_slot(boost::bind(&VariablesEditor::receiveRemoved, this, _1));
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
		widget = new VariableEditWidget();
		ui.tabWidget->addTab(widget, info.getName().c_str());
		connect(widget, SIGNAL(notifyVariableUpdate(QString)), interpreterConnector, SLOT(commandToInterpreter(QString)));
	}


	hide();
	idx = ui.tabWidget->indexOf(widget);
	ui.tabWidget->blockSignals(true);
	ui.tabWidget->setCurrentIndex(idx);
	ui.tabWidget->blockSignals(false);
	show();
	
	dynamic_cast<VariableEditWidget *>(widget)->loadWidget(info);
}

void VariablesEditor::tabClose(int idx)
{
	ui.tabWidget->removeTab(idx);
	if (ui.tabWidget->count() == 0)
		hide();
}

void VariablesEditor::receiveVarsUpdate(const PR::VariableInfo *data, int num)
{
	using PR::VariableInfo;
	for (int i = 0; i < num; i++)
	{
		const VariableInfo *variable = data + i;
		VariableEditWidget *edit = dynamic_cast<VariableEditWidget *>(findTab(variable->getName().c_str()));

		if (edit == nullptr)
			continue;

		edit->setUpdate(true);
		if (edit->isVisibleTo(this))
			edit->loadWidget(*variable,true);
	}
}

void VariablesEditor::receiveRemoved(vector<string> removed)
{
	for (const string &name : removed)
	{
		QWidget *tab = findTab(QString(name.c_str()));
		if (tab == nullptr)
			continue;
		to_remove.push_back(tab);
	}
}

void VariablesEditor::computationComplate()
{
	for (QWidget *widget : to_remove)
	{
		tabClose(ui.tabWidget->indexOf(widget));
	}
	to_remove.clear();
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

void VariablesEditor::onCurrentTabChanged(int idx)
{
	VariableEditWidget *widget = dynamic_cast<VariableEditWidget*>(ui.tabWidget->widget(idx));
	if (widget && widget->needUpdate())
		emit variableInformationRequest(ui.tabWidget->tabText(idx));
}