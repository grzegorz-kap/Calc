#pragma once

#include <vector>
#include <algorithm>


using std::vector;

namespace PR
{

	template <typename T>
	bool find(const vector<T> &search, const vector<T> &match)
	{
		if (std::find_first_of(search.begin(), search.end(), match.begin(), match.end()) != search.end())
			return true;
		else
			return false;
	}

	template <typename T>
	bool find(const vector<T> &search, const T &value)
	{
		if (std::find(search.begin(), search.end(), value) != search.end())
			return true;
		else
			return false;
	}

	template <typename T>
	void SafeRealase(T * var)
	{
		if (var != nullptr)
		{
			delete var;
			var = nullptr;
		}
	}

	template <typename T>
	string toString(const vector<T> &v)
	{
		string out = "";
		for (vector<T>::const_iterator i = v.begin(); i != v.end(); i++)
		{
			out.append(i->toString() + "\n");
		}
		return out;
	}

	
}