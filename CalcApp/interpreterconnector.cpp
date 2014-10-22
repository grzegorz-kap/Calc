#include "interpreterconnector.h"

InterpreterConnector::InterpreterConnector()
{
	PR::SignalEmitter::get()->connect(boost::bind(&InterpreterConnector::signal_receiver, this, _1, _2));
}

InterpreterConnector::~InterpreterConnector()
{
}

void InterpreterConnector::commandToInterpreter(std::string command)
{
	interpreter.work(command);	
}

void InterpreterConnector::signal_receiver(const char *str, const PR::Data *data) 
{
	int a = 2;
	a = 3 * 3;
}

void InterpreterConnector::interpreterOutput(const std::string &name, const shared_ptr<PR::Data> &data)
{
	int a = 2 + 2;
	return;
}