#include "interpreterconnector.h"

const QString InterpreterConnector::errorHtml = "<br><font color=\"DeepPink\">";
const QString InterpreterConnector::endFontHtml = "</font><br>";

InterpreterConnector::InterpreterConnector()
{
}

InterpreterConnector::~InterpreterConnector()
{
}

void InterpreterConnector::connectToInterpreterSingals()
{
	PR::SignalEmitter::get()->connect_output(boost::bind(&InterpreterConnector::signal_receiver, this, _1, _2));
	PR::SignalEmitter::get()->connect_errors(boost::bind(&InterpreterConnector::errors_receiver, this, _1, _2));
	PR::SignalEmitter::get()->connect_execution_complate(boost::bind(&InterpreterConnector::executionComplate, this));
	PR::SignalEmitter::get()->connect_clear_screen(boost::bind(&InterpreterConnector::clearScreen, this));
}

void InterpreterConnector::executionComplate(void)
{
	emit interpreterResponded();
}

void InterpreterConnector::commandToInterpreter(QString command)
{
	emit executionStarted();
	interpreter.work(command.toStdString());
	executionComplate();
}

void InterpreterConnector::workingDirectoryChanged(QString command)
{
	interpreter.changeWorkingDirectory(command.toStdString().c_str());
}

void InterpreterConnector::updateFile(QString file)
{
	interpreter.updateFile(file.toStdString().c_str());
}

void InterpreterConnector::getInformation(QString variableName)
{
	emit sendVariableInformation(interpreter.getVariableInfo(variableName.toStdString().c_str()));
}

/* Boost signals2 */
void InterpreterConnector::signal_receiver(const char *str, const PR::Data *data)
{
	Sync::get()->console_sem.acquire();
	emit interpreterRespondedHtml("<br>" + QString(+str) + "=<br>" + data->toHtml().c_str() + "<br>");
	//emit interpreterResponded(data->toString().c_str());
}

void InterpreterConnector::errors_receiver(const char *str, int position)
{
	emit interpreterError(errorHtml + str + endFontHtml);
	executionComplate();
}