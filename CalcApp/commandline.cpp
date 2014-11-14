#include "commandline.h"

CommandLine::CommandLine(QWidget *parent)
	: QPlainTextEdit(parent)
{
	commandIdx = 0;
	historyFlag = false;
	setPlaceholderText(">> Enter command here");
	highlighter = new Highlighter(document());
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

	if (e->key() == Qt::Key_C && e->modifiers()&Qt::ControlModifier)
	{
		PR::SignalEmitter::get()->call_stop();
	}
	

	if ((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) && !(e->modifiers()&Qt::ShiftModifier))
	{
		addToHistory();
		commandIdx = commandHistory.size() - 1;
		emit commandEntered(toPlainText());
		clear();
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
		return;


	if (commandHistory.size())
		appendPlainText(commandHistory[commandIdx]);
	
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