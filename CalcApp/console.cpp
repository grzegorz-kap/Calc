#include "console.h"

Console::Console(QWidget *parent)
	: QTextBrowser(parent)
{
	document()->setMaximumBlockCount(3000);
}

Console::~Console()
{

}

void Console::append(QString s)
{
	QTextBrowser::append(s);
	cursorToEnd();
	Sync::get()->console_sem.release();
}

void Console::appendWithoutRealase(QString s)
{
	QTextBrowser::append(">> "+s + "\n");
	cursorToEnd();
}

void Console::insertHtml(QString html)
{
	QTextBrowser::insertHtml(html);
	cursorToEnd();
	Sync::get()->console_sem.release();
}

void Console::cursorToEnd()
{
	QTextCursor c = textCursor();
	c.movePosition(QTextCursor::End);
	setTextCursor(c);
}

void Console::clear()
{
	setText("");
}
