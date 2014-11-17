#include "variablesinfos.h"


VariablesInfos::VariablesInfos(QWidget *parent)
	: QTableWidget(parent)
{
}

VariablesInfos::~VariablesInfos()
{

}

void VariablesInfos::connectSlots()
{
	SignalEmitter::get()->connect_added_variables_slot(boost::bind(&VariablesInfos::addNewVariables, this, _1, _2));
	SignalEmitter::get()->connect_updated_variables_slot(boost::bind(&VariablesInfos::updateVariables, this, _1, _2));
	SignalEmitter::get()->connect_removed_variables_slot(boost::bind(&VariablesInfos::removeVariables,this, _1, _2));

}

void VariablesInfos::addCell(const VariableInfo *data)
{
	setSortingEnabled(false);
	int idx = rowCount();
	this->insertRow(idx);
	setItem(idx, 0, createCell(data->getName().c_str()));
	setItem(idx, 1, createCell(data->getValue().c_str()));
	setItem(idx, 2, createCell(data->getType().c_str()));
	setItem(idx, 3, createCell(data->getMin().c_str()));
	setItem(idx, 4, createCell(data->getMax().c_str()));
	setSortingEnabled(true);
	viewport()->update();
}

void VariablesInfos::addNewVariables(const VariableInfo *data, int num)
{
	for (int i = 0; i < num; i++)
	{
		const VariableInfo *variable = data + i;
		addCell(variable);
	}
}

void VariablesInfos::updateVariables(const VariableInfo *data, int num)
{
	for (int i = 0; i < num; i++)
	{
		const VariableInfo *variable = data + i;
		int row = findInCol(0, variable->getName().c_str());
		
		if (row < 0)
			addCell(variable);
		else
			updateCell(row, variable);
	}
}

void VariablesInfos::updateCell(int idx, const VariableInfo *data)
{
	item(idx, 1)->setText(QString(data->getValue().c_str()));
	item(idx, 2)->setText(QString(data->getType().c_str()));
	item(idx, 3)->setText(QString(data->getMin().c_str()));
	item(idx, 4)->setText(QString(data->getMax().c_str()));
	viewport()->update();
}

void VariablesInfos::removeVariables(const char **data, int num)
{

}

int VariablesInfos::findInCol(int col, const QString &match)
{
	int rows = rowCount();
	for (int i = 0; i < rows; i++)
	{
		QString text = item(i, col)->text();
		if (text == match)
			return i;
	}
	return -1;
}
