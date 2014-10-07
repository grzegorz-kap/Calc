#ifndef INTERPRETERCONNECTOR_H
#define INTERPRETERCONNECTOR_H

#include <string>
#include <QObject>
#include "Calc\Interpreter.h"

class InterpreterConnector : public QObject
{
	Q_OBJECT

private:
	PR::Interpreter interpreter;
public:
	InterpreterConnector(QObject *parent);
	~InterpreterConnector();

private slots:
	void commandToInterpreter(std::string command);

signals:
	void interpreterResponded(QString respond);
};

#endif // INTERPRETERCONNECTOR_H
