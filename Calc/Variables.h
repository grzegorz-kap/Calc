#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

#include "Data.h"

using std::string;
using std::map;
using std::vector;
using std::shared_ptr;

namespace PR
{
	class Variables
	{
		map<string, shared_ptr<Data>> mem;
		vector<string> added;
		vector<string> removed;
		vector<string> updated;
		bool main;
	
	public:
		Variables(bool main=false);
		~Variables();

		shared_ptr<Data> get(const string &name, bool ex = true);

		auto set(const string &name, const shared_ptr<Data> &data)
			->std::pair < std::map<string, shared_ptr<Data>>::iterator, bool > ;

		void clearAddedAndRemoved();
		
		vector<string>& getAddedRef(){ return added; }
		vector<string>& getRemovedRef(){ return removed; }
		vector<string>& getUpdatedRef(){ return updated; }
	};

}
