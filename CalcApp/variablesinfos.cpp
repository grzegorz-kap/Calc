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

void VariablesInfos::addNewVariables(const VariableInfo *data, int num)
{

	for (int i = 0; i < num; i++)
	{
		const VariableInfo *variable = data + i;
		int rowIndex = rowCount();
		insertRow(rowIndex);
		setItem(rowIndex, 0, createCell(variable->getName().c_str()));
		setItem(rowIndex, 1, createCell(variable->getValue().c_str()));
		setItem(rowIndex, 2, createCell(variable->getType().c_str()));
		setItem(rowIndex, 3, createCell(variable->getMin().c_str()));
		setItem(rowIndex, 4, createCell(variable->getMax().c_str()));
	}
}

void VariablesInfos::updateVariables(const VariableInfo *data, int num)
{
	for (int i = 0; i < num; i++)
	{
		const VariableInfo *variable = data + i;
		int row = findInCol(0, variable->getName().c_str());
		if (row < 0)
			continue;

		item(row, 1)->setText(QString(variable->getValue().c_str()));
		item(row, 2)->setText(QString(variable->getType().c_str()));
		item(row, 3)->setText(QString(variable->getMin().c_str()));
		item(row, 4)->setText(QString(variable->getMax().c_str()));
		viewport()->update();
	}
	
}

void VariablesInfos::removeVariables(const char **data, int num)
{

}

int VariablesInfos::findInCol(int col, const QString &match)
{
	int rows = rowCount();
	for (int i = 0; i < rows; i++)
	{
		if (item(i, col)->text() == match)
			return i;
	}
	return -1;
}