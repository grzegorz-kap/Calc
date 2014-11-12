#ifndef SCRIPTEDITWIDGET_H
#define SCRIPTEDITWIDGET_H

#include <QTextEdit>
#include <qfile.h>

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

private:
	bool updated;
	QString filePath;
	
	
};

#endif // SCRIPTEDITWIDGET_H
