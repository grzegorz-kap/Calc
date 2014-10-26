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
		}
		else
			onExternalFunction(args,name);
		
	}

	void CodeExecutor::onExternalFunction(const vector<shared_ptr<Data>> &args,const string &name)
	{
		if (++recursions > recursion_limit)
			throw CalcException("Error in '" + name + "'. Maximum recursion limit of " +
			std::to_string(recursion_limit) + " reached.", (*i)->getPosition());
		
		auto function = FunctionFactory::load_external(name);
		CodeExecutor exec(function,args);
		exec.start();

		recursions--;

		const vector<string>& output = function.getOutput();
		shared_ptr<Output> results = make_shared<Output>();
		for (const string &str : output)
		{
			auto result = exec.vars_ref.find(str);
			if (result == exec.vars_ref.end())
				break;
			results->add(result->second);
		}
		stack.push_back(results);
		
	}
}