#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include "Data.h"
#include "Operator.h"

namespace PR
{
	//! Mapa z istotna kolejnoscia wstawiania elementow.
	template<class KEY, class VALUE>
	class i_order_map
	{
		std::unordered_map<KEY, VALUE> map;
		std::vector<KEY> vec;
		int i;
	public:

		i_order_map();
		~i_order_map();

		void insert(const KEY &key, const VALUE &value);
		int length() const;
		const std::vector<KEY> & getVec() const;
		VALUE & operator[](const KEY &b);
	};
}
