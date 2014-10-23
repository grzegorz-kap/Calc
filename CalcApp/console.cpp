#include "console.h"

Console::Console(QWidget *parent)
	: QTextBrowser(parent)
{

}

Console::~Console()
{

}

void Console::append(const QString &s)
{
	QTextBrowser::append(s);
	QTextCursor c = textCursor();
	c.movePosition(QTextCursor::End);
	setTextCursor(c);
}
