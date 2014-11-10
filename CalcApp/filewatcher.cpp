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

void FileWatcher::changedFile(QString path)
{
	QString temp = path;
	temp.remove(QRegExp("\.m$"));
	emit fileUpdated(temp);
}

void FileWatcher::changed(QString path)
{
	mFilesWatcher.removePaths(dir.entryList());
	dir.refresh();
	mFilesWatcher.addPaths(dir.entryList());
	emit sendFileList(dir.entryList());
}

void FileWatcher::fileDialogButtonClicked()
{
	QString new_dir =  QFileDialog::getExistingDirectory();
	if (new_dir == "")
		return;
	setNewDirectory(new_dir);	
}

void FileWatcher::setNewDirectory( QString directory)
{
	if (dir.path() == directory)
		return;
	mFilesWatcher.removePaths(dir.entryList());
	dir.setPath(directory == "" ? QDir::currentPath() : directory);
	changed(directory);
	emit workingDirectoryChanged(dir.path());
}