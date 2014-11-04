#pragma once

#include <map>
#include <string>
#include <memory>

#include "Data.h"

using std::string;
using std::map;
using std::shared_ptr;

namespace PR
{
	class Variables
	{
		map<string, shared_ptr<Data>> mem;
	
	public:
		Variables()
		{
		};

		~Variables()
		{
		};

		shared_ptr<Data> get(const string &name, bool ex = true)
		{
			auto result = mem.find(name);
			if (result == mem.end())
			{
				if (!ex)
					return nullptr;
				throw string("Variable '" + name + "' not found!");
			}
			return result->second;
		}

		auto set(const string &name, const shared_ptr<Data> &data)
			-> std::pair < std::map<string, shared_ptr<Data>>::iterator, bool >
		{
			auto result = mem.insert({ name, data });
			if (result.second == false)
				result.first->second = data;
			return result;
		}

	};

}
