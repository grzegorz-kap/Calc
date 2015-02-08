#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QFileSystemWatcher>
#include <qstringlist.h>
#include <qdir.h>
#include <qregexp.h>
#include <qfiledialog.h>

class FileWatcher : public QFileSystemWatcher
{
	Q_OBJECT
private:
	QDir dir;
public:
	FileWatcher(const QString &dir,QObject *parent=0);
	~FileWatcher();
signals:
	void sendFileList(QStringList list);
	void fileUpdated( QString );
	void workingDirectoryChanged( QString );

public slots:
	void changed( QString  path);
	void fileDialogButtonClicked();
	void setNewDirectory( QString path);
	
};

#endif // FILEWATCHER_H
