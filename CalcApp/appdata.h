#ifndef APPDATA_H
#define APPDATA_H

#include <QObject>
#include <qstandardpaths.h>
#include <qstringlist.h>
#include <qcombobox.h>
#include <qfile.h>
#include <qdir.h>
#include <qtextstream.h>

class AppData : public QObject
{
	Q_OBJECT

private:


public:

	static const QString dirHistory;
	static const QString commandHistory;
	static const QString calcFolder;
	static const QString app_name;

	AppData(QObject *parent);
	~AppData();

	static void writeDirHistory(QComboBox *ptr);
	static void loadDirHistory(QComboBox *ptr);
private:
	static void createCalcFolder();
};

#endif // APPDATA_H
