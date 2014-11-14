#ifndef SCRIPTEDITWIDGET_H
#define SCRIPTEDITWIDGET_H

#include <QTextEdit>
#include <qevent.h>
#include <qfile.h>
#include <qfiledialog.h>
#include "highlighter.h"

class ScriptEditWidget : public QTextEdit
{
	Q_OBJECT

public:
	ScriptEditWidget(QWidget *parent);
	~ScriptEditWidget();

	bool isUpdated() const;
	QString getFilePath() const;

	void setUpdated(bool q);
	void setFilePath(QString path);
	bool readFromFile();
	bool saveToFile();

	QString askForPathToSave();

	static void setWorkingDirectory(const QString &directory);
	static QString getWorkingDirectory();
	static QFont defaultFont;

signals:
	void fileSaved();

private:
	bool updated;
	QString filePath;
	static QString workingDirectory;
	Highlighter *highlighter;
	
protected:
	virtual void keyPressEvent(QKeyEvent *ev);
	
	
};

#endif // SCRIPTEDITWIDGET_H
