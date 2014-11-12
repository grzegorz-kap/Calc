#include "scripteditwidget.h"

ScriptEditWidget::ScriptEditWidget(QWidget *parent)
	: QTextEdit(parent)
{
	updated = false;
	
	filePath= "";
}

ScriptEditWidget::~ScriptEditWidget()
{

}


bool ScriptEditWidget::isUpdated() const
{
	return updated;
}

QString ScriptEditWidget::getFilePath() const
{
	return filePath;
}

void ScriptEditWidget::setUpdated(bool p)
{
	updated = p;
}

void ScriptEditWidget::setFilePath(QString path)
{
	filePath = path;
}

bool ScriptEditWidget::readFromFile()
{
	if (filePath == "")
		return false;

	QFile file(filePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return true;

	if (!file.atEnd())
		setText(file.readAll());
	
	file.close();

	return true;
}


