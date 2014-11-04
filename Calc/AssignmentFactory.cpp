#include "stdafx.h"
#include "AssignmentFactory.h"


namespace PR
{
	IAssignment* AssignmentFactory::get(TOKEN_CLASS _class)
	{
		switch (_class)
		{
		case TOKEN_CLASS::ID: 
			return new AssignmentSingle();
		case TOKEN_CLASS::MATRIX_START: 
			return new AssignmentMulti();
		case TOKEN_CLASS::FUNCTON_ARGS_END:
			return new AssignmentSubscripted();
		default:
			throw CalcException("Unrecognized assignment target");
		}
	}
}
