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

	void IAssignment::loadTarget(instr_iter &start, instr_iter &end)
	{
		throw CalcException("Cannot load assignment target!");
	}

	void IAssignment::doAssignment(Variables &vars, stack_iterator &first, stack_iterator &last, AssignmentsData &assignment)
	{
		throw CalcException("Unimplemented assignment");
	};

	variables_map_pair IAssignment::assign(Variables &vars, const string &key, const shared_ptr<Data> &data)
	{
		return vars.set(key, data);
	}

	int IAssignment::getTargetSize() const
	{
		return 0;
	}
}