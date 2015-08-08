#pragma once
#include "IAssignment.h"
#include "Output.h"

namespace PR
{
	class AssignmentSingle :
		public IAssignment
	{
		shared_ptr<Token> target;
	public:
		AssignmentSingle();
		~AssignmentSingle();

		virtual void loadTarget(instr_iter &start, instr_iter &end) override;
		virtual void doAssignment(Variables &vars, stack_iterator &first, stack_iterator &last, AssignmentsData &assignment) override;
		virtual int getTargetSize() const override;
		virtual IAssignment * castToAssignment() override;
		void setTargetName(string &&name);
		virtual string getLexeme() const override;
	};
}
