#include "stdafx.h"
#include "VariableInfo.h"


namespace PR
{
	VariableInfo::VariableInfo(const string &name, Data * data)
	{
		this->name = name;

		if (data == nullptr)
			return;

		type = data->getTypeName();

		try{ value = data->getValueInfoString(); }
		catch (const CalcException &ex){ value == "Unknown"; }
		
		try{ value = data->getValueInfoString(); }
		catch (const CalcException &ex){ min = "Unknown"; }

		try{ min = data->minValueString(); }
		catch (const CalcException &ex){ min = "Unknown"; }
		
		try{ max = data->maxValueString(); }
		catch (const CalcException &ex){ max = "Unknown"; }
	}


	VariableInfo::~VariableInfo()
	{
	}

	const char * VariableInfo::getName() const
	{
		return name.c_str();
	}

	const char * VariableInfo::getValue() const
	{
		return value.c_str();
	}

	const char * VariableInfo::getMax() const
	{
		return max.c_str();
	}

	const char *  VariableInfo::getMin() const
	{
		return min.c_str();
	}

	const char * VariableInfo::getType() const
	{
		return type.c_str();
	}
}
