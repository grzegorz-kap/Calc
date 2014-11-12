#ifndef CALCAPP_H
#define CALCAPP_H

#include <QtWidgets/QMainWindow>
#include <qthread.h>
#include <qmetatype.h>
#include <qdir.h>

#include "ui_calcapp.h"
#include "interpreterconnector.h"
#include "FileWatcher.h"
#include "variablesinfos.h"
#include "variableseditor.h"
#include "ScriptEditor.h"


class CalcApp : public QMainWindow
{
	Q_OBJECT

public:
	CalcApp(QWidget *parent = 0);
	~CalcApp();

private:
	Ui::CalcAppClass ui;
	InterpreterConnector *interpreterConnector;
	FileWatcher fileWatcher;
	VariablesEditor variablesEditor;
	ScriptEditor scriptEditor;

	void closeEvent(QCloseEvent *ev);

};

#endif // CALCAPP_H
