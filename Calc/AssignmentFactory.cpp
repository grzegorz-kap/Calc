#include "stdafx.h"
#include "AssignmentFactory.h"


namespace PR
{
	unique_ptr<IAssignment> AssignmentFactory::get(TOKEN_CLASS _class)
	{
		switch (_class)
		{
		case TOKEN_CLASS::ID: 
			return make_unique<AssignmentSingle>();
		case TOKEN_CLASS::MATRIX_START: 
			return make_unique<AssignmentMulti>();
		case TOKEN_CLASS::FUNCTON_ARGS_END:
			return make_unique<AssignmentSubscripted>();
		default:
			throw CalcException("Unrecognized assignment target");
		}
	}
}
