#pragma once
#include "Data.h"

#include <vector>
#include <memory>

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
	};
}

