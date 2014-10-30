#include "filewatcher.h"

FileWatcher::FileWatcher(const QString &path,QObject *parent)
	: QFileSystemWatcher(parent),
	dir(path)
{
	QStringList filters;
	filters << "*.m";
	dir.setNameFilters(filters);

	connect(&mFilesWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(changedFile(const QString&)));
}

FileWatcher::~FileWatcher()
{

}

void FileWatcher::changedFile(const QString &path)
{
	QString temp = path;
	temp.remove(QRegExp("\.m$"));
	emit fileUpdated(temp);
}

void FileWatcher::changed(const QString &path)
{
	mFilesWatcher.removePaths(dir.entryList());
	dir.refresh();
	mFilesWatcher.addPaths(dir.entryList());
	emit sendFileList(dir.entryList());
}
