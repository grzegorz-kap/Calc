#ifndef DIRECTORYCOMBOBOX_H
#define DIRECTORYCOMBOBOX_H

#include <QComboBox>
#include <qsortfilterproxymodel.h>

#include "appdata.h"

class DirectoryComboBox : public QComboBox
{
	Q_OBJECT

public:
	DirectoryComboBox(QWidget *parent);
	~DirectoryComboBox();

private:

public slots :
	void workingDirectoryChanged(const QString &directory);
	void sort();
	
};

#endif // DIRECTORYCOMBOBOX_H
