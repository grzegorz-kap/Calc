#include "scripteditwidget.h"

QString ScriptEditWidget::workingDirectory = "";

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

void ScriptEditWidget::keyPressEvent(QKeyEvent *ev)
{
	if (ev->key() == Qt::Key_S && (ev->modifiers()&Qt::ControlModifier))
	{
		saveToFile();
	}
	else
		QTextEdit::keyPressEvent(ev);
}


bool ScriptEditWidget::saveToFile()
{
	if (!updated)
		return false;

	if (filePath == "")
	{
		filePath = askForPathToSave();
	}

	if (filePath == "")
		return false;

	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	file.write(toPlainText().toStdString().c_str());
	file.close();


	updated = false;
	emit fileSaved();
	return true;
}

QString ScriptEditWidget::askForPathToSave()
{
	return QFileDialog::getSaveFileName(
		this,
		"Save script",
		workingDirectory+"/"+QDir(filePath).dirName(),
		tr("Scripts (*.m)")
		);
}

void ScriptEditWidget::setWorkingDirectory(const QString &directory)
{
	workingDirectory = directory;
}

QString ScriptEditWidget::getWorkingDirectory()
{
	return workingDirectory;
}