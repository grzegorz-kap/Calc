#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

#include "Data.h"

namespace PR
{
	class Output :
		public Data
	{
	public:
		Output();
		~Output();

		static shared_ptr<Output> cast(const shared_ptr<Data> &data,bool ex=true);

	private:
		vector<shared_ptr<Data>> out;
	};

}
