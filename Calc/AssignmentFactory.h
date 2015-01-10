#ifndef ASSIGNMENT_FACTORY_H
#define ASSIGNMENT_FACTORY_H

#pragma once

#include "AssignmentSingle.h"
#include "AssignmentMulti.h"
#include "AssignmentSubscripted.h"

#include <memory>

using std::unique_ptr;
using std::make_unique;

namespace PR
{
	class AssignmentFactory
	{
	public:
		static unique_ptr<IAssignment> get(TOKEN_CLASS _class);
	};
}

#endif

