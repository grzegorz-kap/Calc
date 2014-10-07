#include "interpreterconnector.h"

InterpreterConnector::InterpreterConnector(QObject *parent)
	: QObject(parent)
{

}

InterpreterConnector::~InterpreterConnector()
{

}

void InterpreterConnector::commandToInterpreter(std::string command)
{
	emit interpreterResponded(QString(interpreter.work(command).c_str()));
}