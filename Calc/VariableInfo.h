
#pragma once

#include "export.h"
#include "Data.h"
#include "CalcException.h"

#include <string>
#include <memory>

using std::string;
using std::weak_ptr;

namespace PR
{
	//! Klasa z informacjami o zmiennej.
	class CALC_API VariableInfo
	{
	private:
		weak_ptr<Data> data;
		string name;
		static const string expired;
	public:

		VariableInfo(){};
		VariableInfo(const string &name, const shared_ptr<Data> &ptr);
		~VariableInfo();

		string getName() const;
		string getValue() const;
		string getMin() const;
		string getMax() const;
		string getType() const;

		int get_rows() const;
		int get_cols() const;

		bool is_scalar() const;

		string get_cell(int i, int j) const;
	};
}


