#include "interpreterconnector.h"

int InterpreterConnector::a = 10;

InterpreterConnector::InterpreterConnector()
{

}

InterpreterConnector::~InterpreterConnector()
{

}

void InterpreterConnector::commandToInterpreter(std::string command)
{
	std::string ab = std::to_string(InterpreterConnector::a++);
	emit interpreterResponded(QString(ab.c_str()));
	QThread::sleep(2);
	
}