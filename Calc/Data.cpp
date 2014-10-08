#include "stdafx.h"
#include "Data.h"


namespace PR
{
	std::unordered_map<std::type_index, TYPE> Data::TYPE_MAP =
		std::unordered_map<std::type_index, TYPE>();

	bool Data::TYPE_MAP_BUILDED = false;

	Data::Data()
	{
	}


	Data::~Data()
	{
	}
}