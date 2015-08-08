#ifndef ASSIGNMENT_SUB_H
#define ASSIGNMENT_SUB_H

#pragma once
#include "IAssignment.h"
#include "TypePromotor.h"
namespace KLab
{
	class AssignmentSubscripted :
		public IAssignment
	{
		vector<shared_ptr<Token>> onp;
		shared_ptr<Token> variable;

		static vector<shared_ptr<Data>>(*executor)(const vector<shared_ptr<Token>>&, Variables &);
	public:

		AssignmentSubscripted();
		~AssignmentSubscripted();

		virtual void loadTarget(instr_iter &start, instr_iter &end) override;
		virtual void doAssignment(Variables &vars, stack_iterator &first, stack_iterator &last, AssignmentsData &assignment) override;
		virtual int getTargetSize() const override;
		virtual IAssignment * castToAssignment() override;
		vector<shared_ptr<Token>>& getOnpRef();
	};
}

#endif
