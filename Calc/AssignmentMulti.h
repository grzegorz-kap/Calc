#pragma once
#include "IAssignment.h"
#include "AssignmentFactory.h"

#include <memory>
using std::unique_ptr;

namespace PR
{
	class AssignmentMulti :
		public IAssignment
	{
		vector<unique_ptr<IAssignment>> target;
	public:
		AssignmentMulti();
		~AssignmentMulti();

		virtual void loadTarget(vector<shared_ptr<Token>>::iterator &start, vector<shared_ptr<Token>>::iterator &end) override;
		virtual IAssignment * castToAssignment() override;

		virtual int getTargetSize() const
		{
			return target.size();
		}

		virtual void doAssignment(Variables &vars,
			vector<shared_ptr<Data>>::iterator &first,
			vector<shared_ptr<Data>>::iterator &last,
			vector<std::pair<std::map<string, shared_ptr<Data>>::iterator, bool>> &assignment) override;

		void prepareIterators(vector<shared_ptr<Data>>::iterator &data, vector<shared_ptr<Data>>::iterator &start, 
			vector<shared_ptr<Data>>::iterator &end , int &size);
	};

}
