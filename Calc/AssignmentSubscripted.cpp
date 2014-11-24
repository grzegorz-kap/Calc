#include "stdafx.h"
#include "AssignmentSubscripted.h"


namespace PR
{
	AssignmentSubscripted::AssignmentSubscripted()
		:IAssignment(ASSIGNMENT_TYPE::SUBSCRIPTED)
	{
	}

	AssignmentSubscripted::~AssignmentSubscripted()
	{
	}

	void AssignmentSubscripted::loadTarget(instr_iter &start, instr_iter &end)
	{
		if (start == end)
			throw CalcException("Error in subscripted assignment");

		if ((*start)->getClass() != TOKEN_CLASS::FUNCTON_ARGS_END)
			throw CalcException("Unexpected token during subscripted assignment!", (*start)->getPosition());

		int balance = 0;
		auto result = std::find_if(++start, end, [&balance](const shared_ptr<Token> &token) -> bool{
			if (token->getClass() == TOKEN_CLASS::FUNCTION && balance == 0)
				return true;

			if (token->getClass() == TOKEN_CLASS::FUNCTION)
				balance--;
			
			if (token->getClass() == TOKEN_CLASS::FUNCTON_ARGS_END)
				balance++;
			return false;
		});

		if (result == end)
			throw CalcException("Error parsing subscripted assignment!");
		onp.clear();
		onp.insert(onp.begin(), start, result);
		variable = std::move(*result);
		start = std::next(result);
	}

	void AssignmentSubscripted::doAssignment(Variables &vars, stack_iterator &first, stack_iterator &last, AssignmentsData &assignment)
	{
		if (first == last)
			throw CalcException("Too few arguments on right side of assignment!");
		
		shared_ptr<Data> var = nullptr;
		try{
			var = vars.get(variable->getLexemeR());
		}
		catch (const string &ex)
		{
			throw CalcException("Error in subscripted assignment."+ex);
		}

		if (var->isComplexNumber())
		{
			TypePromotor::promote(var,IMatrixBuilder::getAssociatedType(var->_type));
		}

		auto address = executor(onp, vars);
		TypePromotor::promote(address, var->_type);

		TypePromotor::promote(*first, var->_type);
		switch (address.size())
		{
		case 2: var->assignAt(address[0], address[1], *first);	break;
		case 1: var->assignAt(address[0], *first);				break;
		case 0: var->assignAt(*first);							break;
		}

		assignment.push_back(vars.set(variable->getLexemeR(), var));
	}

	int AssignmentSubscripted::getTargetSize() const
	{
		return 1;
	}

	vector<shared_ptr<Token>>& AssignmentSubscripted::getOnpRef()
	{ 
		return onp; 
	}

	IAssignment* AssignmentSubscripted::castToAssignment()
	{
		return dynamic_cast<AssignmentSubscripted*>(this);
	}
}
