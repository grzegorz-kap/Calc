#include "stdafx.h"
#include "Output.h"


namespace PR
{
	Output::Output()
	{
		_ty = DATA_TYPE::OUTPUT;
	}


	Output::~Output()
	{
	}

	shared_ptr<Output> Output::cast(const shared_ptr<Data> &data, bool ex)
	{
		auto p = std::dynamic_pointer_cast<Output>(data);

		if (ex && p == nullptr)
			CalcException("Cannot cast to 'Output' type!");

		return p;
	}
}
