#ifndef VARIABLESEDITOR_H
#define VARIABLESEDITOR_H

#include <QWidget>
#include <qtablewidget.h>
#include "ui_variableseditor.h"

#include "VariableEditWidget.h"

class VariablesEditor : public QWidget
{
	Q_OBJECT

public:
	VariablesEditor(QWidget *parent = 0);
	~VariablesEditor();

private:
	Ui::VariablesEditor ui;

public slots:
	void onVariableSelection(QTableWidgetItem *item);

signals:


};

#endif // VARIABLESEDITOR_H
