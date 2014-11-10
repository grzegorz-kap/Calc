#ifndef VARIABLEEDITWIDGET_H
#define VARIABLEEDITWIDGET_H

#include <QWidget>
#include "ui_VariableEditWidget.h"
#include "Calc\VariableInfo.h"

class VariableEditWidget : public QWidget
{
	Q_OBJECT

public:
	VariableEditWidget(QWidget *parent = 0);
	~VariableEditWidget();

	void loadWidget(const PR::VariableInfo &info);

public slots:
	void onItemChanged(QTableWidgetItem *item);

signals:
	void notifyVariableUpdate(QString command);

private:
	Ui::VariableEditWidget ui;
	QString variableName;
};

#endif // VARIABLEEDITWIDGET_H
