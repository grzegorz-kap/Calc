#include "interpreterconnector.h"

InterpreterConnector::InterpreterConnector()
{
	PR::SignalEmitter::get()->connect(boost::bind(&InterpreterConnector::signal_receiver, this, _1, _2));
}

InterpreterConnector::~InterpreterConnector()
{
}

void InterpreterConnector::commandToInterpreter(const std::string &command)
{
	interpreter.work(command);	
}

/* Boost signals2 */
void InterpreterConnector::signal_receiver(const char *str, const PR::Data *data) 
{
	emit interpreterResponded(QString(str) + "=\n" + data->toString().c_str());
}