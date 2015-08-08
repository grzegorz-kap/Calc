#pragma once
#include "IAssignment.h"
#include "AssignmentFactory.h"
#include <memory>
using std::unique_ptr;
namespace KLab
{
	class AssignmentMulti : public IAssignment
	{
	private:
		vector<unique_ptr<IAssignment>> target;

	public:
		AssignmentMulti();
		~AssignmentMulti();

		virtual void loadTarget(instr_iter &start, instr_iter &end) override;
		virtual void doAssignment(Variables &vars, stack_iterator &first, stack_iterator &last, AssignmentsData &assignment) override;
		virtual int getTargetSize() const;
		virtual IAssignment * castToAssignment() override;
		auto getTargetConstReference() -> const decltype(target) &;
		void prepareIterators(stack_iterator &data, stack_iterator &start, stack_iterator &end, int &size);
	};
}
