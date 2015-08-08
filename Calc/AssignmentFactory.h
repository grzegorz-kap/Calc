#ifndef ASSIGNMENT_FACTORY_H
#define ASSIGNMENT_FACTORY_H

#pragma once

#include "AssignmentSingle.h"
#include "AssignmentMulti.h"
#include "AssignmentSubscripted.h"

#include <memory>

using std::unique_ptr;
using std::make_unique;

namespace KLab
{
	//! Fabryka operacji przypisania.
	/*!
		Zwraca odpowiedni obiekt implementujacy interfejs operacji przypisania
		*/
	class AssignmentFactory
	{
	public:
		//! Zwraca odpowiedni typ przypisania.
		/*!
		* @param _class rodzaj symbolu leksykalnego, na podstawie ktorego zotanie zwrocona odpowiednia implementacja interfejsu przypisania
		*/
		static unique_ptr<IAssignment> get(TOKEN_CLASS _class);
	};
}

#endif
