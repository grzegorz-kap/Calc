#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QObject>
#include <qplaintextedit.h>
#include <qevent.h>
#include <qvector.h>

#include "Calc\SignalEmitter.h"

class CommandLine : public QPlainTextEdit
{
	Q_OBJECT

private:
	QString command;
	QVector<QString> commandHistory;
	int commandIdx;
	bool historyFlag;
public:
	CommandLine(QWidget *parent);
	~CommandLine();

private:
	void setCursorPosition(int n);
	void keyPressEvent(QKeyEvent* e);
	void addToHistory();
	void onKeyUpOrDown(int key);
signals:
	void commandEntered(const QString &command);
};

#endif // COMMANDLINE_H
