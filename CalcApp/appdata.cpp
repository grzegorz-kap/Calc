#include "appdata.h"

const QString AppData::app_name = "KapiLab";

const QString AppData::calcFolder =
	QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/" + AppData::app_name;

const QString AppData::dirHistory = AppData::calcFolder + "/dirHistory.m";

const QString AppData::commandHistory = AppData::calcFolder + "/commandHistory.m";


AppData::AppData(QObject *parent)
	: QObject(parent)
{

}

AppData::~AppData()
{

}

void AppData::createCalcFolder()
{
	if (!QDir(calcFolder).exists())
		QDir().mkdir(calcFolder);
}

void AppData::appendToFile(const QString &fileName, const QString &data)
{
	createCalcFolder();
	QFile file(fileName);
	if (!file.open(QIODevice::Append | QIODevice::Text))
		return;
	QTextStream stream(&file);
	stream.setCodec(QTextCodec::codecForName("UTF-8"));
	stream << data;
	file.close();
}

void AppData::appendToDirHistory(const QString &command)
{
	appendToFile(dirHistory, command + "\n");
}

void AppData::writeDirHistory(QComboBox *dir)
{
	createCalcFolder();
	QFile file(dirHistory);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream s(&file);
	s.setCodec(QTextCodec::codecForName("UTF-8"));
	int N = dir->count();
	for (int i = 0; i < N; i++)
	{
		s << dir->itemText(i) << "\n" ;
	}
	file.close();
}

void AppData::loadDirHistory(QComboBox *dir)
{
	QFile file(dirHistory);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	while (!file.atEnd())
	{
		QString element = file.readLine();
		if (!element.isEmpty())
		{
			element.remove("\n");
			dir->addItem(element);
		}
	}
	file.close();
}

void AppData::appendToCommandHistory(const QString &command)
{
	appendToFile(commandHistory, command + "\n");
}

void AppData::loadCommandHistory(QTreeWidget *widget)
{
	QFile file(commandHistory);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTreeWidgetItem *current = nullptr;
	while (!file.atEnd())
	{
		QString line = file.readLine();
		line.remove("\n");

		if (line.size() == 0)
			continue;
		

		if (line[0] == '%')
		{
			current = new QTreeWidgetItem(QStringList(line));
			widget->addTopLevelItem(current);
		}
		else if (current != nullptr)
		{
			current->addChild(new QTreeWidgetItem(QStringList(line)));
		}
	}
	file.close();
}