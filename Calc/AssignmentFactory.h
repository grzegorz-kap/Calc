#ifndef ASSIGNMENT_FACTORY_H
#define ASSIGNMENT_FACTORY_H

#pragma once

#include "AssignmentSingle.h"
#include "AssignmentMulti.h"
#include "AssignmentSubscripted.h"

namespace PR
{
	class AssignmentFactory
	{
	public:
		static IAssignment* get(TOKEN_CLASS _class);
	};
}

#endif

