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

	void loadWidget(const PR::VariableInfo &info,bool rememberSelection=false);
	void setUpdate(bool val){ updated = val; }
	bool needUpdate()const{ return updated; }

public slots:
	void onItemChanged(QTableWidgetItem *item);
	void onTabChanged(){ loadWidget(info); }
signals:
	void notifyVariableUpdate(QString command);

private:
	
	Ui::VariableEditWidget ui;
	QString variableName;
	bool updated;
	PR::VariableInfo info;
};

#endif // VARIABLEEDITWIDGET_H
