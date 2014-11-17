#ifndef VARIABLESINFOS_H
#define VARIABLESINFOS_H

#include <QTableWidget>
#include <qcolor.h>

#include "Calc\VariableInfo.h"
#include "Calc\SignalEmitter.h"

using namespace PR;

class VariablesInfos : public QTableWidget
{
	Q_OBJECT

public:
	VariablesInfos(QWidget *parent);
	~VariablesInfos();

	void connectSlots();
	void addNewVariables(const VariableInfo *data, int num);
	void updateVariables(const VariableInfo *data, int num);
	void removeVariables(const char **, int num);

	
private:
	static QTableWidgetItem* createCell(const QString &str) { return new QTableWidgetItem(str); }
	void addCell(const VariableInfo *data);
	void updateCell(int idx, const VariableInfo *data);
	int findInCol(int col, const QString &match);
};

#endif // VARIABLESINFOS_H
