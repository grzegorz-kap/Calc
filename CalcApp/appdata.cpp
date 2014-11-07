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

void AppData::writeDirHistory(QComboBox *dir)
{
	createCalcFolder();
	QFile file(dirHistory);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream s(&file);

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
