#include "stdafx.h"
#include "AssignmentSingle.h"

namespace KLab
{
	AssignmentSingle::AssignmentSingle()
		:IAssignment(ASSIGNMENT_TYPE::SINGLE)
	{
	}

	AssignmentSingle::~AssignmentSingle()
	{
	}

	void AssignmentSingle::loadTarget(instr_iter &start, instr_iter &end)
	{
		if (start == end)
			throw CalcException("Cannot load assignment target! Empty instruction");

		target = std::move(*start);

		if (target->getClass() != TOKEN_CLASS::ID)
			throw CalcException("Unexpected symbol in assignment target", target->getPosition());

		start++;
	}

	IAssignment * AssignmentSingle::castToAssignment()
	{
		return dynamic_cast<AssignmentSingle *>(this);
	}

	int AssignmentSingle::getTargetSize() const
	{
		return 1;
	}

	string AssignmentSingle::getLexeme() const
	{
		return target->getLexeme();
	}

	void AssignmentSingle::doAssignment(Variables &vars, stack_iterator &first, stack_iterator &last, AssignmentsData &assignment)
	{
		if (first == last)
			throw CalcException("Assign expression is incomplate!");

		if ((*first)->isOutput())
		{
			auto source = std::dynamic_pointer_cast<Output>(*first)->getOutput();
			if (source.size() < 1)
				throw CalcException("Too many output arguments.");
			assignment.push_back(IAssignment::assign(vars, target->getLexemeR(), source[0]));
		}
		else
			assignment.push_back(IAssignment::assign(vars, target->getLexemeR(), *first));
	}

	void AssignmentSingle::setTargetName(string &&name)
	{
		if (target != nullptr)
			target->setLexeme(std::move(name));
		else
			target = make_shared<Token>(std::move(name), TOKEN_CLASS::ID);
	}
}