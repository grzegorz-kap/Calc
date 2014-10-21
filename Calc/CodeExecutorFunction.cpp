#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	void CodeExecutor::onFunction()
	{
		string name = (*i)->getLexeme();
		auto ii = find(TOKEN_CLASS::FUNCTON_ARGS_END, true);
		vector<shared_ptr<Data>> args(std::next(ii), stack.end());
		stack.erase(ii, stack.end());
		
		auto function = FunctionFactory::load_in(name);
		if (function != nullptr)
		{
			function->set(args);
			stack.push_back(function->run());
			return;
		}
		
		auto functione = FunctionFactory::load_external(name);
	}
}