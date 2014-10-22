#ifndef INTERPRETERCONNECTOR_H
#define INTERPRETERCONNECTOR_H

#include <string>
#include <QObject>
#include "Calc\Interpreter.h"
#include "Calc\SignalEmitter.h"

class InterpreterConnector : public QObject
{
	Q_OBJECT
private:
	PR::Interpreter interpreter;
	void signal_receiver(const char *, const PR::Data *);
public:
	InterpreterConnector();
	~InterpreterConnector();

private slots:
	void commandToInterpreter(std::string command);
	void interpreterOutput(const std::string &name, const shared_ptr<PR::Data> &data);
};

#endif // INTERPRETERCONNECTOR_H
