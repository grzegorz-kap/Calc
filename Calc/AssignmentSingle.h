#pragma once
#include "IAssignment.h"

namespace PR
{
	class AssignmentSingle :
		public IAssignment
	{
		shared_ptr<Token> target;
	public:
		AssignmentSingle();
		~AssignmentSingle();

		virtual void loadTarget(vector<shared_ptr<Token>>::iterator &start,vector<shared_ptr<Token>>::iterator &end) override;
		
		virtual IAssignment* castToAssignment() override;
		
		virtual void doAssignment(Variables &vars,
			vector<shared_ptr<Data>>::iterator &first,
			vector<shared_ptr<Data>>::iterator &last,
			vector<std::pair<std::map<string, shared_ptr<Data>>::iterator, bool>> &assignment) override;
		
		virtual int getTargetSize() const override { return 1; }

		void setTargetName(string &&name);
	};
}

