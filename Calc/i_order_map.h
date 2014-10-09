#pragma once

#include <unordered_map>
#include <vector>


namespace PR
{
	template<class KEY,class VALUE>
	class i_order_map
	{
		std::unordered_map<KEY,VALUE> map;
		std::vector<KEY> vec;
		int i;
	public:
		i_order_map():i(0){};
		~i_order_map(){};

		void insert(const KEY &key, const VALUE &value)
		{
			map[key] = value;
			vec.push_back(key);
		}

		int length() const 
		{
			return vec.size();
		}

		const std::vector<KEY> & getVec() const
		{
			return vec;
		}

		VALUE & operator[](const KEY &b)
		{
			return map[b];
		}
	};

}
