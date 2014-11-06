#include "stdafx.h"
#include "CodeExecutor.h"

namespace PR
{
	
	void CodeExecutor::onFunctionArgs()
	{
		/*
			Information about expected number of parameters returned from function
		*/
		if (i != ip->begin() && std::prev(i)->get()->getClass() == TOKEN_CLASS::ASSIGNMENT_TARGET)
		{
			stack.push_back(make_shared<Token>(TOKEN_CLASS::FUNCTON_ARGS_END, -1, 
				std::prev(i)->get()->castToAssignment()->getTargetSize()));
			return;
		}
		stack.push_back(make_shared<Token>(TOKEN_CLASS::FUNCTON_ARGS_END,-1,-1));
	}

	void CodeExecutor::onMatrixAll()
	{
		stack.push_back(make_shared<Token>(TOKEN_CLASS::MATRIX_ALL, (*i)->getPosition()));
	}

	void CodeExecutor::onFunction()
	{
		const string &name = (*i)->getLexemeR();

		auto ii = find(TOKEN_CLASS::FUNCTON_ARGS_END, true);
		vector<shared_ptr<Data>> args(std::next(ii), stack.end());
		int num = (*ii)->cast_token()->getParam();
		stack.erase(ii, stack.end());

		try{
			onVariableFunction(args, vars_ref.get(name));
			return;
		} 
		catch (const string &ex)
		{
		}

		auto function = FunctionFactory::load_in(name);
		if (function != nullptr)
		{
			function->set(args, num > 0 ? num : 1);
			stack.push_back(function->run());
		}
		else
			onExternalFunction(args, name);

	}

	void CodeExecutor::onVariableFunction( vector<shared_ptr<Data>> &args, shared_ptr<Data> &var)
	{
		int size = args.size();
		if (size > 2)
			throw CalcException("Too many arguments while accessing variables cells");

		TYPE convertToType = var->_type;

		for (int i = args.size() - 1; i >= 0; i--)
			if (args[i]->_type != convertToType && !args[i]->isToken(TOKEN_CLASS::MATRIX_ALL))
				TypePromotor::convertTo(convertToType, args[i], args[i]);		
		
		if (size == 2)
			stack.push_back(var->getAt(args[0], args[1]));
		else if (size == 1)
			stack.push_back(var->getAt(args[0]));
		else
			stack.push_back(var->getAt());
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
			auto result = exec.vars_ref.get(str);
			if (result == nullptr)
				break;
			results->add(result);
		}
		stack.push_back(results);
	}
}