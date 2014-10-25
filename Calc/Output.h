#pragma once
#include "Data.h"

#include <vector>
#include <memory>
#include <algorithm>

using std::vector;
using std::shared_ptr;

namespace PR
{
	class Output :
		public Data
	{
		vector<shared_ptr<Data>> out;
	public:

		Output();
		~Output();

		void add(const shared_ptr<Data> &item)
		{
			out.push_back(item);
		}

		vector<shared_ptr<Data>>& getOutput()
		{
			return out;
		}

		virtual bool isOutput() const override
		{
			return true;
		}

		virtual Output * cast_output() override
		{
			return dynamic_cast<Output *>(this);
		}

		virtual TYPE max_type() const override
		{
			return (*std::max_element(out.begin(), out.end(),
				[](const shared_ptr<Data> &a, const shared_ptr<Data> &b){return a->_type < b->_type; }))->_type;
		}

		virtual bool isNumeric() const override
		{
			for (auto iter = out.begin(); iter != out.end(); ++iter)
			{
				if (!(*iter)->isNumeric())
					return false;
			}
			return true;
		}

	};
}

