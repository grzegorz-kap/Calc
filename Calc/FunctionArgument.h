#pragma once

#include <memory>
#include <string>

using std::shared_ptr;
using std::string;

#include "Data.h"

namespace PR
{
	class FunctionArgument
	{
		string name;
		DATA_TYPE _type;
		shared_ptr<Data> data;
	public:
		FunctionArgument();
		~FunctionArgument();

		shared_ptr<Data>& getData(){ return data; }
		DATA_TYPE get_Type(){ return _type; }
		string getName(){ return name; }
	};
}

