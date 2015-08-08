#include "stdafx.h"
#include "AssignmentOperator.h"

namespace KLab
{
	AssignmentOperator::AssignmentOperator()
		:Operator("=", 200, 2, EVAULATED::LEFT)
	{
	}

	AssignmentOperator::~AssignmentOperator()
	{
	}
}