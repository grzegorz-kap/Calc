#include "commandline.h"

CommandLine::CommandLine(QWidget *parent)
	: QPlainTextEdit(parent)
{
	this->appendPlainText(">> ");
	commandIdx = 0;
	historyFlag = false;
}

CommandLine::~CommandLine()
{

}

void CommandLine::setCursorPosition(int n)
{
}

void CommandLine::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Up || e->key() == Qt::Key_Down)
	{
		onKeyUpOrDown(e->key());
		return;
	}
	

	if ((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) && !(e->modifiers()&Qt::ShiftModifier))
	{
		addToHistory();
		commandIdx = commandHistory.size() - 1;

		QString command = toPlainText();
		emit commandEntered(command);
		command.remove(0, 3);
		emit commandEntered(command.toStdString());

		clear();
		appendPlainText(">> ");

		return;
	}
	commandIdx = commandHistory.size()-1;
	historyFlag = false;

	QPlainTextEdit::keyPressEvent(e);
}

void CommandLine::onKeyUpOrDown(int key)
{
	if (historyFlag)
	{
		if (key == Qt::Key_Up && commandIdx > 0)
			commandIdx--;
		if (key == Qt::Key_Down&& commandIdx < commandHistory.size() )
			commandIdx++;
	}
	historyFlag = true;

	clear();
	if (commandIdx == commandHistory.size())
	{
		appendPlainText(">> ");
		return;
	}

	if (commandHistory.size())
		appendPlainText(commandHistory[commandIdx]);
	else
		appendPlainText(">> ");
	
}

void CommandLine::addToHistory()
{
	QString temp(toPlainText());

	if (temp.size() == 0 || temp == ">> ")
		return;

	if (commandHistory.size() && commandHistory.last() == temp)
		return;
	
	commandHistory.push_back(temp);
}