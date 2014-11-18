#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

#include "Data.h"
#include "VariableInfo.h"

using std::string;
using std::map;
using std::vector;
using std::shared_ptr;

namespace PR
{
	class Variables
	{
		map<string, shared_ptr<Data>> mem;
		bool main;
	
	public:
		Variables(bool main=false);
		~Variables();

		shared_ptr<Data> get(const string &name, bool ex = true);
		auto getIterator(const string &name, bool ex = true)
			-> std::map<string, shared_ptr<Data>>::iterator;
		auto set(const string &name, const shared_ptr<Data> &data)
			->std::pair < std::map<string, shared_ptr<Data>>::iterator, bool > ;

		void getUpdated(vector<VariableInfo> &added , vector<VariableInfo> &updated) const;
	};

}
