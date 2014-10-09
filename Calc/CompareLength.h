#pragma once

#include <string>

namespace PR
{
	struct CompareLength
	{
		bool operator()(const std::string &l, const std::string &r) const
		{
			return l.length() > r.length();
		}
	};
}