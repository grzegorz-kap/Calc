#include "stdafx.h"
#include "AssignmentMulti.h"


namespace PR
{
	AssignmentMulti::AssignmentMulti()
		: IAssignment(ASSIGNMENT_TYPE::MULTI)
	{

	}

	AssignmentMulti::~AssignmentMulti()
	{
	}

	void AssignmentMulti::loadTarget(instr_iter &start, instr_iter &end)
	{
		if ((*start)->getClass() != TOKEN_CLASS::MATRIX_START)
			throw CalcException("Wrong start of multiassignment!");
		for (start = std::next(start); start != end; )
		{
			if ((*start)->getClass() == TOKEN_CLASS::VERSE_END)
			{
				start++;
				if ((*start)->getClass() != TOKEN_CLASS::MATRIX_END)
					throw CalcException("Wrong assignment", (*start)->getPosition());
				break;
			}

			unique_ptr<IAssignment> assignment(AssignmentFactory::get((*start)->getClass()));
			if (assignment->_assignment_type == ASSIGNMENT_TYPE::MULTI)
				throw CalcException("Nasted multi assignment!");

			assignment->loadTarget(start, end);
			target.push_back(std::move(assignment));
		}
		start++;
	}

	void AssignmentMulti::doAssignment(Variables &vars, stack_iterator &first, stack_iterator &last, AssignmentsData &assignment)
	{
		if (first==last)
			throw CalcException("Too many output arguments!");
		
		int size = 0;
		vector<shared_ptr<Data>>::iterator begin;
		vector<shared_ptr<Data>>::iterator end;

		prepareIterators(first, begin, end,size);

		if (size<target.size())
			throw CalcException("Too many output arguments!");

		for (const unique_ptr<IAssignment> &unit : target)
		{
			unit->doAssignment(vars, begin++, end, assignment);
		}
	}


	void AssignmentMulti::prepareIterators(stack_iterator &data, stack_iterator &start, stack_iterator &end, int &size)
	{
		if ((*data)->isOutput())
		{
			auto & vec = (*data)->cast_output()->getOutput();
			size = vec.size();
			start = vec.begin();
			end = vec.end();
		}
		else
		{
			size = 1;
			start = data;
			end = std::next(data);
		}
	}

	IAssignment* AssignmentMulti::castToAssignment()
	{
		return dynamic_cast<AssignmentMulti *>(this);
	}

	int AssignmentMulti::getTargetSize() const
	{
		return target.size();
	}

	auto AssignmentMulti::getTargetConstReference()
		-> const decltype(target) &
	{
		return target;
	}
}
