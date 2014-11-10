#include "interpreterconnector.h"

const QString InterpreterConnector::errorHtml = "<font color=\"DeepPink\">";
const QString InterpreterConnector::endFontHtml = "</font><br>";

InterpreterConnector::InterpreterConnector()
{
	
}

InterpreterConnector::~InterpreterConnector()
{
}

void InterpreterConnector::commandToInterpreter(QString command)
{
	interpreter.work(command.toStdString());	
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
	emit interpreterRespondedHtml("<br>"+QString(+str) + "=<br>" + data->toHtml().c_str()+"<br>");
}

void InterpreterConnector::errors_receiver(const char *str, int position)
{
	emit interpreterError(errorHtml + str + endFontHtml);
}