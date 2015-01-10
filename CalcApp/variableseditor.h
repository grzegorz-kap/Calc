#ifndef VARIABLESEDITOR_H
#define VARIABLESEDITOR_H

#include <QWidget>
#include <qtablewidget.h>

#include "Calc\VariableInfo.h"
#include "Calc\SignalEmitter.h"

#include "ui_variableseditor.h"
#include "VariableEditWidget.h"
#include "interpreterconnector.h"


class VariablesEditor : public QWidget
{
	Q_OBJECT

public:
	VariablesEditor(QWidget *parent = 0);
	~VariablesEditor();

	void connectToInterpretSingals();
	void setInterpreter(InterpreterConnector *ptr){ interpreterConnector = ptr; }

private:
	Ui::VariablesEditor ui;
	InterpreterConnector *interpreterConnector;
	QWidget* findTab(const QString &name);

	void receiveRemoved(vector<string> removed);
	void receiveVarsUpdate(const PR::VariableInfo *data, int num);

public slots:
	void onVariableSelection(QTableWidgetItem *item);
	void receiveVariableInformation(PR::VariableInfo info);
	void onCurrentTabChanged(int idx);
signals:
	void variableInformationRequest(QString varName);
};

#endif // VARIABLESEDITOR_H
