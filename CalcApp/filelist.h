#ifndef FILELIST_H
#define FILELIST_H

#include <QListWidget>

class FileList : public QListWidget
{
	Q_OBJECT

public:
	FileList(QWidget *parent);
	~FileList();

private:
	public slots :
		void set(QStringList list);
};

#endif // FILELIST_H
