#ifndef VARIABLEEDITWIDGET_H
#define VARIABLEEDITWIDGET_H

#include <QWidget>
#include "ui_VariableEditWidget.h"

class VariableEditWidget : public QWidget
{
	Q_OBJECT

public:
	VariableEditWidget(QWidget *parent = 0);
	~VariableEditWidget();

private:
	Ui::VariableEditWidget ui;
};

#endif // VARIABLEEDITWIDGET_H
