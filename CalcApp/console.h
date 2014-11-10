#ifndef CONSOLE_H
#define CONSOLE_H

#include <qtextbrowser.h>
#include "Sync.h"

class Console : public QTextBrowser
{
	Q_OBJECT

public:
	Console(QWidget *parent);
	~Console();

public slots:
	void append(QString );
	void appendWithoutRealase(QString);
	void insertHtml(QString );
private:
	void cursorToEnd();
};

#endif // CONSOLE_H
