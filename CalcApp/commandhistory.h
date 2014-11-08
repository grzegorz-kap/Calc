#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include <QTreeWidget>
#include <qdatetime.h>
#include <appdata.h>

class CommandHistory : public QTreeWidget
{
	Q_OBJECT

public:
	CommandHistory(QWidget *parent);
	~CommandHistory();

	void insertCurrentDate();
	void insertTopLevel(const QString &string);
	
public slots:
	void onItemDoubleClicked(QTreeWidgetItem *item, int);
	void insertCommand(const QString &command);

private:
	QTreeWidgetItem *prevItem;
	QTreeWidgetItem *prevCommandItem;

signals:
	void executeCommand(const QString &);
};

#endif // COMMANDHISTORY_H
