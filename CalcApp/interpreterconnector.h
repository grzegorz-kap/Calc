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
	InterpreterConnector();
	~InterpreterConnector();

private slots:
	void commandToInterpreter(std::string command);
};

#endif // INTERPRETERCONNECTOR_H
