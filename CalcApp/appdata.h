#ifndef APPDATA_H
#define APPDATA_H

#include <QObject>
#include <qstandardpaths.h>
#include <qstringlist.h>
#include <qcombobox.h>
#include <qfile.h>
#include <qdir.h>
#include <qtextstream.h>
#include <qtreewidget.h>
#include <qtextcodec.h>

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

	static void appendToDirHistory(const QString &dir);
	static void writeDirHistory(QComboBox *ptr);
	static void loadDirHistory(QComboBox *ptr);
	static void appendToCommandHistory(const QString &command);
	static void loadCommandHistory(QTreeWidget *ptr);
private:
	static void createCalcFolder();
	static void appendToFile(const QString &fileName, const QString &data);
};

#endif // APPDATA_H
