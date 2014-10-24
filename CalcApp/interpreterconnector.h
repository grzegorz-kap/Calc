#ifndef INTERPRETERCONNECTOR_H
#define INTERPRETERCONNECTOR_H

#include <string>
#include <QObject>
#include "Calc\Interpreter.h"
#include "Calc\SignalEmitter.h"


#include "Sync.h"

class InterpreterConnector : public QObject
{
	Q_OBJECT

private:
	
	PR::Interpreter interpreter;
	

	static const QString errorHtml;
	static const QString endFontHtml;

public:
	void signal_receiver(const char *, const PR::Data *);
	void errors_receiver(const char *, int);
	InterpreterConnector();
	~InterpreterConnector();

private slots:
	void commandToInterpreter(const std::string &command);

signals:
	void interpreterResponded(const QString&);
	void interpreterError(const QString &);
};

#endif // INTERPRETERCONNECTOR_H
