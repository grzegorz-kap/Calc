#include "stdafx.h"
#include "VariableInfo.h"


namespace PR
{
	const string VariableInfo::expired = "expired";

	VariableInfo::VariableInfo(const string &name, const shared_ptr<Data> &ptr)
		:name(name),
		data(ptr)
	{
	}


	VariableInfo::~VariableInfo()
	{
	}

	string VariableInfo::getName() const
	{
		return name;
	}

	string VariableInfo::getValue() const
	{
		auto sp = data.lock();
		if (sp)
			return sp->getValueInfoString();
		return expired;
	}

	string VariableInfo::getMax() const
	{
		auto sp = data.lock();
		if (sp)
			return sp->maxValueString();
		return expired;
	}

	string  VariableInfo::getMin() const
	{
		auto sp = data.lock();
		if (sp)
			return sp->minValueString();
		return expired;
	}

	string VariableInfo::getType() const
	{
		auto sp = data.lock();
		if (sp)
			return sp->getTypeName();
		return expired;
	}

	int VariableInfo::get_cols() const
	{
		auto sp = data.lock();
		if (sp)
			return sp->get_cols_int();
		return 0;
	}

	int VariableInfo::get_rows() const
	{
		auto sp = data.lock();
		if (sp)
			return sp->get_rows_int();
		return 0;
	}

	string VariableInfo::get_cell(int i, int j) const
	{
		auto sp = data.lock();
		if (sp)
			return sp->get_cell_string(i, j);
		return expired;
	}
}
