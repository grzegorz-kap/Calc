#include "filewatcher.h"

FileWatcher::FileWatcher(const QString &path,QObject *parent)
	: QFileSystemWatcher(parent),
	dir(path)
{
	QStringList filters;
	filters << "*.m";
	dir.setNameFilters(filters);
}

FileWatcher::~FileWatcher()
{

}

void FileWatcher::changed(const QString &path)
{
	dir.refresh();
	emit sendFileList(dir.entryList());
}
