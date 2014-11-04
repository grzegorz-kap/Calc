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

	void AssignmentSubscripted::loadTarget(vector<shared_ptr<Token>>::iterator &start, vector<shared_ptr<Token>>::iterator &end)
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

	void AssignmentSubscripted::doAssignment(Variables &vars,
		vector<shared_ptr<Data>>::iterator &first,
		vector<shared_ptr<Data>>::iterator &last,
		vector<std::pair<std::map<string, shared_ptr<Data>>::iterator, bool>> &assignment)
	{
		auto address = executor(onp, vars);
	}
}
