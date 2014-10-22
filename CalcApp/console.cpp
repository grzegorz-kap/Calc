#include "console.h"

Console::Console(QWidget *parent)
	: QTextEdit(parent)
{

}

Console::~Console()
{

}

void Console::append(const QString &s)
{
	QTextEdit::append(s);
	QTextCursor c = textCursor();
	c.movePosition(QTextCursor::End);
	setTextCursor(c);
}
