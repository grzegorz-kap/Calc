#ifndef VARIABLESEDITOR_H
#define VARIABLESEDITOR_H

#include <QWidget>
#include <qtablewidget.h>

#include "Calc\VariableInfo.h"

#include "ui_variableseditor.h"
#include "VariableEditWidget.h"
#include "interpreterconnector.h"


class VariablesEditor : public QWidget
{
	Q_OBJECT

public:
	VariablesEditor(InterpreterConnector *interpreter,QWidget *parent = 0);
	~VariablesEditor();

private:
	Ui::VariablesEditor ui;
	InterpreterConnector *interpreterConnector;
	QWidget* findTab(const QString &name);

public slots:
	void onVariableSelection(QTableWidgetItem *item);
	void receiveVariableInformation(PR::VariableInfo info);
signals:
	void variableInformationRequest(QString varName);
};

#endif // VARIABLESEDITOR_H
