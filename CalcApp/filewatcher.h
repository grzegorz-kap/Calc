#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QFileSystemWatcher>
#include <qstringlist.h>
#include <qdir.h>

class FileWatcher : public QFileSystemWatcher
{
	Q_OBJECT
private:
	QDir dir;
public:
	FileWatcher(const QString &dir,QObject *parent=0);
	~FileWatcher();
signals:
	void sendFileList(const QStringList &list);

public slots:
	void changed(const QString & path);

	
};

#endif // FILEWATCHER_H
