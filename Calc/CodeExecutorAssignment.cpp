#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	void CodeExecutor::defaultAssignment()
	{
		auto target = make_shared<Assignment>();
		target->getTarget().push_back(make_shared<Token>("ans", TOKEN_CLASS::ID));
		stack.insert(stack.begin(), std::move(target));
		onAssignment();
	}

	void CodeExecutor::onAssignment()
	{
		if (stack.size() < 2)
			throw CalcException("!");

		auto &target = std::dynamic_pointer_cast<Assignment>(*stack.begin())->getTarget();
		auto data = std::next(stack.begin());

		if ((*data)->isOutput())
		{
			auto source = std::dynamic_pointer_cast<Output>(*data)->getOutput();
			auto oo = source.begin();
			for (auto ii = target.begin(); ii != target.end(); ii++)
			{
				if (oo == source.end())
					throw CalcException("Too many output arguments!");
				assignment.push_back(vars_ref.insert({ (*ii)->getLexemeR(), *oo }));
				if (assignment.back().second == false)
					assignment.back().first->second = *oo;
				oo++;
			}
		}
		else
		{
			assignment.push_back(vars_ref.insert({ target[0]->getLexemeR(), *data }));
			if (assignment.back().second == false)
				assignment.back().first->second = *data;
		}
		stack.erase(stack.begin(), stack.begin() + 2);
		assignment_flag = true;
	}

}