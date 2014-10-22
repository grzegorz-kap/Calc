#include "interpreterconnector.h"

InterpreterConnector::InterpreterConnector()
{
}

InterpreterConnector::~InterpreterConnector()
{
}

void InterpreterConnector::commandToInterpreter(std::string command)
{
	interpreter.work(command);	
}