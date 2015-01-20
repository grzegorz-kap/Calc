#pragma once

#include <vector>
#include <algorithm>
#include <string>

using std::vector;

namespace PR
{
	//! Funkcja wyszukuje pierwsze wyst¹pienie wartosci z zestawu wartosci.
	/*!
	*	Funkcja sprawdza czy przynajmniej jeden element z zestawu wartosci znajduje sis w przeszukiwanej tablicy.
	*	@param search to przeszukiwana tablica
	*	@param match to zestaw wartoœci które nale¿y wyszukaæ
	*	@return wynik wyszukiwania
	*/
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