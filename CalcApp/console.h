#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextEdit>

class Console : public QTextEdit
{
	Q_OBJECT

public:
	Console(QWidget *parent);
	~Console();

public slots:
	void append(const QString &);

};

#endif // CONSOLE_H
