#pragma once

#include "export.h"
#include "Data.h"
#include "CalcException.h"

#include <string>

using std::string;

namespace PR
{
	class CALC_API VariableInfo
	{
	private:
		string name;
		string value;
		string min;
		string max;
		string type;
	public:
		VariableInfo(){};
		VariableInfo(const string &name,Data *);
		~VariableInfo();

		const char * getName() const;
		const char * getValue() const;
		const char * getMin() const;
		const char * getMax() const;
		const char * getType() const;
	};
}

