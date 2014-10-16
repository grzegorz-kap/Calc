#ifndef INTERPRETERCONNECTOR_H
#define INTERPRETERCONNECTOR_H

#include <string>
#include <QObject>
#include "Calc\Interpreter.h"
#include <qthread.h>

class InterpreterConnector : public QObject
{
	Q_OBJECT

private:
	static int a;
	PR::Interpreter interpreter;
public:
	InterpreterConnector();
	~InterpreterConnector();

private slots:
	void commandToInterpreter(std::string command);

signals:
	void interpreterResponded(QString respond);
};

#endif // INTERPRETERCONNECTOR_H
