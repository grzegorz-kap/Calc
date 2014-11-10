#ifndef VARIABLESINFOS_H
#define VARIABLESINFOS_H

#include <QTableWidget>

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

	int findInCol(int col, const QString &match);
private:
	static QTableWidgetItem* createCell(const QString &str) { return new QTableWidgetItem(str); }
};

#endif // VARIABLESINFOS_H
