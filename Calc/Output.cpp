#include "stdafx.h"
#include "Output.h"

namespace PR
{
	Output::Output()
	{
		_type = TYPE::OUTPUT;
		_extern = false;
	}

	Output::~Output()
	{
	}

	void Output::add(const shared_ptr<Data> &item)
	{
		out.push_back(item);
	}

	vector<shared_ptr<Data>>& Output::getOutput()
	{
		return out;
	}

	bool Output::isOutput() const
	{
		return true;
	}

	Output * Output::cast_output()
	{
		return dynamic_cast<Output *>(this);
	}

	TYPE Output::max_type() const
	{
		if (out.size() == 0)
			return _type;
		return (*std::max_element(out.begin(), out.end(),
			[](const shared_ptr<Data> &a, const shared_ptr<Data> &b){return a->_type < b->_type; }))->_type;
	}

	bool Output::isNumeric() const
	{
		for (auto iter = out.begin(); iter != out.end(); ++iter)
		{
			if (!(*iter)->isNumeric())
				return false;
		}
		return true;
	}
}