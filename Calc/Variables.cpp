#include "stdafx.h"
#include "Variables.h"


namespace PR
{
	Variables::Variables(bool main)
		:main(main)
	{
	};

	Variables::~Variables()
	{
	};

	shared_ptr<Data> Variables::get(const string &name, bool ex)
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

	auto Variables::set(const string &name, const shared_ptr<Data> &data)
		-> std::pair < std::map<string, shared_ptr<Data>>::iterator, bool >
	{
		auto result = mem.insert({ name, data });
		if (result.second == false)
		{
			result.first->second = data;
			if (main)
				updated.push_back(name);
		}
		else if (main)
			added.push_back(name);

		return result;
	}

	void Variables::clearAddedAndRemoved()
	{
		added.clear();
		removed.clear();
	}
}
