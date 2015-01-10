#pragma once
#include "Data.h"

#include <vector>
#include <memory>
#include <algorithm>

using std::vector;
using std::shared_ptr;

namespace PR
{
	class Output : public Data
	{
		vector<shared_ptr<Data>> out;
	public:

		bool _extern;

		Output();
		~Output();
		int getArgumentsNumber() const { return out.size(); }
		void add(const shared_ptr<Data> &item);
		vector<shared_ptr<Data>>& getOutput();
		virtual bool isOutput() const override;
		virtual Output * cast_output() override;
		virtual TYPE max_type() const override;
		virtual bool isNumeric() const override;

	};
}

