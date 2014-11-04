#include "stdafx.h"
#include "IAssignment.h"


namespace PR
{
	IAssignment::IAssignment(const ASSIGNMENT_TYPE &_type)
		:_assignment_type(_type)
	{
		set_class(TOKEN_CLASS::ASSIGNMENT_TARGET);
	}


	IAssignment::~IAssignment()
	{
	}

	auto IAssignment::assign(Variables &vars,const string &key,const shared_ptr<Data> &data)
		->std::pair < std::map<string, shared_ptr<Data>>::iterator, bool >
	{
		return vars.set(key, data);
	}
}
