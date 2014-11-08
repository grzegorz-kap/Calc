#include "directorycombobox.h"

DirectoryComboBox::DirectoryComboBox(QWidget *parent)
	: QComboBox(parent)
{
	AppData::loadDirHistory(this);
	//sort();
}

DirectoryComboBox::~DirectoryComboBox()
{

}

void DirectoryComboBox::workingDirectoryChanged(const QString &dir)
{
	int result = findText(dir);
	if (result == -1)
	{
		addItem(dir);
		AppData::appendToDirHistory(dir);
		setCurrentIndex(count() - 1);
	}
	else
		setCurrentIndex(result);
}

void DirectoryComboBox::sort()
{
	// for sorting you need the following 4 lines
	QSortFilterProxyModel* proxy = new QSortFilterProxyModel(this);  // <--
	proxy->setSourceModel(model());                            // <--
	// combo's current model must be reparented,
	// otherwise QComboBox::setModel() will delete it
	model()->setParent(proxy);                                 // <--
	setModel(proxy);                                           // <--
	// sort
	model()->sort(0); 
}
