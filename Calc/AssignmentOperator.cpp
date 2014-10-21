#include "stdafx.h"
#include "AssignmentOperator.h"


namespace PR
{
	AssignmentOperator::AssignmentOperator()
		:Operator("=",100,2,EVAULATED::LEFT)
	{
	}


	AssignmentOperator::~AssignmentOperator()
	{
	}
}
