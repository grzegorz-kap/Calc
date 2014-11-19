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

	variables_map_iter Variables::getIterator(const string &name, bool ex)
	{
		auto result = mem.find(name);
		if (result == mem.end() &&ex)
			throw string("Variable '" + name + "' not found!");
		return result;
	}

	variables_map_pair Variables::set(const string &name, const shared_ptr<Data> &data)
	{
		shared_ptr<Data> temp(data->copy());

		auto result = mem.insert({ name, temp });
		if (result.second == false)
		{
			result.first->second = temp;
			temp->_updated = true;
		}
		else
		{
			temp->_added = true;
		}
		return result;
	}

	void Variables::getUpdated(vector<VariableInfo> &added, vector<VariableInfo> &updated) const
	{
		added.clear();
		updated.clear();
		for (const auto &element : mem)
		{
			if (element.second->_added)
			{
				added.push_back(VariableInfo(element.first, element.second));
			}
			else if (element.second->_updated)
			{
				updated.push_back(VariableInfo(element.first, element.second));
			}
			element.second->_updated = false;
			element.second->_added = false;
		}
	}
}
