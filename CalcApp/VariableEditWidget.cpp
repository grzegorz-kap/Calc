#include "VariableEditWidget.h"

VariableEditWidget::VariableEditWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onItemChanged(QTableWidgetItem*)));
}

VariableEditWidget::~VariableEditWidget()
{

}

void VariableEditWidget::loadWidget(const PR::VariableInfo &info)
{
	variableName = info.getName().c_str();
	int rows = info.get_rows();
	int cols = info.get_cols();

	QTableWidget *table = ui.tableWidget;
	table->clearContents();
	
	table->blockSignals(true);
	for (int i = 0; i < rows; i++)
	{
		table->insertRow(i);
		for (int j = 0; j < cols; j++)
		{
			if (i == 0)
				table->insertColumn(j);
			table->setItem(i, j, new QTableWidgetItem(QString(info.get_cell(i, j).c_str())));
		}
	}
	table->blockSignals(false);
}

void VariableEditWidget::onItemChanged(QTableWidgetItem *item)
{
	QString command = variableName + "(" + QString::number(item->row()+1) + "," + QString::number(item->column()+1) + ")";
	command.append("=" + item->text() + ";");
	emit notifyVariableUpdate(command);
}
