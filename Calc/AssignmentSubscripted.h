#ifndef ASSIGNMENT_SUB_H
#define ASSIGNMENT_SUB_H

#pragma once
#include "IAssignment.h"
#include "TypePromotor.h"
namespace PR
{
	class AssignmentSubscripted :
		public IAssignment
	{
		vector<shared_ptr<Token>> onp;
		shared_ptr<Token> variable;
		
		static vector<shared_ptr<Data>>(*executor)(const vector<shared_ptr<Token>>&,Variables &);
	public:

		AssignmentSubscripted();
		~AssignmentSubscripted();

		virtual void loadTarget(vector<shared_ptr<Token>>::iterator &start, vector<shared_ptr<Token>>::iterator &end) override;

		virtual void doAssignment(Variables &vars,
			vector<shared_ptr<Data>>::iterator &first,
			vector<shared_ptr<Data>>::iterator &last,
			vector<std::pair<std::map<string, shared_ptr<Data>>::iterator, bool>> &assignment) override;

		virtual int getTargetSize() const override
		{
			return 1;
		}

		virtual IAssignment* castToAssignment() override
		{
			return dynamic_cast<AssignmentSubscripted *>(this);
		}
		vector<shared_ptr<Token>>& getOnpRef() { return onp; }
	};
}

#endif

