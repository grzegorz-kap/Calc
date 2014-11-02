#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "ComplexNumber.h"

using std::vector;

namespace PR
{
	template <class T>
	class ComplexNumber;

	template <typename T>
	bool find(const vector<T> &search, const vector<T> &match)
	{
		return std::find_first_of(search.begin(), search.end(), match.begin(), match.end()) != search.end()
	}

	template <typename T>
	bool find(const vector<T> &search, const T &value)
	{
		return std::find(search.begin(), search.end(), value) != search.end();
	}

	template <typename T>
	void SafeRealase(T ** ptr)
	{
		if (*ptr != nullptr)
		{
			delete *ptr;
			*ptr = nullptr;
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