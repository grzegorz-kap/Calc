#include "filewatcher.h"

FileWatcher::FileWatcher(const QString &path,QObject *parent)
	: 
	dir(path)
{
	QStringList filters;
	filters << "*.m";
	dir.setNameFilters(filters);
}

FileWatcher::~FileWatcher()
{

}


void FileWatcher::changed(QString path)
{
	dir.refresh();
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
	removePath(dir.path());
	dir.setPath(directory == "" ? dir.path() : directory);
	dir.refresh();
	addPath(dir.path());
	emit workingDirectoryChanged(dir.path());
	emit sendFileList(dir.entryList());
}