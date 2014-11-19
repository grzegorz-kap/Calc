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
	InterpreterConnector();
	~InterpreterConnector();

	void connectStopComputing(){ interpreter.connectStopComputing(); }
	void connectToInterpreterSingals();
	void signal_receiver(const char *, const PR::Data *);
	void errors_receiver(const char *, int);
	void executionComplate(void);

public slots:
	void workingDirectoryChanged(QString dir);

private slots:
	void commandToInterpreter(QString command);
	void updateFile(QString);
	void getInformation( QString variableName);
signals:
	void interpreterResponded(QString);
	void interpreterRespondedHtml(QString);
	void interpreterResponded();
	void interpreterError(QString);
	void sendVariableInformation(PR::VariableInfo);
};

#endif // INTERPRETERCONNECTOR_H
