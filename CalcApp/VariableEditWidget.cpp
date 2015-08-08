#include "VariableEditWidget.h"

VariableEditWidget::VariableEditWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onItemChanged(QTableWidgetItem*)));
	updated = true;
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

VariableEditWidget::~VariableEditWidget()
{
}

void VariableEditWidget::loadWidget(const PR::VariableInfo &info, bool rembemberSelection)
{
	if (updated == false)
		return;

	scalar = info.is_scalar();

	variableName = info.getName().c_str();
	int rows = info.get_rows();
	int cols = info.get_cols();

	QTableWidget *table = ui.tableWidget;

	int current_row = table->currentRow();
	int current_col = table->currentColumn();

	int current_row_count = table->rowCount();
	int current_col_count = table->columnCount();

	table->blockSignals(true);
	for (int i = 0; i < rows; i++)
	{
		if (i >= current_row_count)
			table->insertRow(i);
		for (int j = 0; j < cols; j++)
		{
			if (i == 0 && j >= current_col_count)
				table->insertColumn(j);

			QTableWidgetItem *item = table->item(i, j);

			if (item == nullptr)
				table->setItem(i, j, new QTableWidgetItem(QString(info.get_cell(i, j).c_str())));
			else
				table->item(i, j)->setText(QString(info.get_cell(i, j).c_str()));
		}
	}

	for (int i = current_row_count - 1; i >= rows; i--)
		table->removeRow(i);
	for (int j = current_col_count - 1; j >= cols; j--)
		table->removeColumn(j);

	table->setColumnCount(cols + 5);
	table->setRowCount(rows + 5);

	if (rembemberSelection)
	{
		table->setCurrentCell(current_row, current_col);
	}

	table->blockSignals(false);
	updated = false;
}

void VariableEditWidget::onItemChanged(QTableWidgetItem *item)
{
	if (item->text().size() == 0)
		return;

	QString command = "";

	if (scalar && (item->column() > 0 || item->row() > 0))
		command += variableName + "=[" + variableName + "];";

	command += variableName + "(" + QString::number(item->row() + 1) + "," + QString::number(item->column() + 1) + ")";
	command += "=" + item->text() + ";";
	emit notifyVariableUpdate(command);
}