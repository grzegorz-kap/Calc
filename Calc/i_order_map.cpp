#include "stdafx.h"
#include "i_order_map.h"

namespace PR
{


	template<class T,class U> 
	i_order_map<T,U>::i_order_map() :i(0)
	{

	}
	
	template<class T, class U> 
	i_order_map<T, U>::~i_order_map()
	{

	}

	template<class T, class U> 
	void i_order_map<T, U>::insert(const T &key, const U &value)
	{
		map[key] = value;
		vec.push_back(key);
	}

	template<class T, class U>
	int i_order_map<T, U>::length() const
	{
		return vec.size();
	}

	template<class T, class U> 
	const std::vector<T> & i_order_map<T, U>::getVec() const
	{
		return vec;
	}

	template<class T, class U> 
	U& i_order_map<T, U>::operator[](const T &b)
	{
		return map[b];
	}

	template class i_order_map < std::string, std::unique_ptr<Operator>(*)(void) > ;
}