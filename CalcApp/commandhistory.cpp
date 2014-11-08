#include "commandhistory.h"

CommandHistory::CommandHistory(QWidget *parent)
	: QTreeWidget(parent)
{
	prevItem = nullptr;
	prevCommandItem = nullptr;
	insertCurrentDate();
}

CommandHistory::~CommandHistory()
{

}

void CommandHistory::insertCurrentDate()
{
	insertTopLevel("%-- " + QDateTime::currentDateTime().toString() + " --%");
}

void CommandHistory::insertTopLevel(const QString &str)
{
	prevItem = new QTreeWidgetItem(QStringList(QString(str)));
	addTopLevelItem(prevItem);
}

void CommandHistory::insertCommand(const QString &str)
{
	if (prevItem == nullptr)
		return;

	if (prevCommandItem != nullptr && prevCommandItem->text(0) == str)
		return;

	prevCommandItem = new QTreeWidgetItem(QStringList(QString(str)));
	prevItem->addChild(prevCommandItem);
	scrollToBottom();
}

void CommandHistory::onItemDoubleClicked(QTreeWidgetItem *item, int idx)
{
	emit executeCommand(item->text(0));
}