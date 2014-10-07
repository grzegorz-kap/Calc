#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::function;

#include "Token.h"
#include "PlusOperator.h"

namespace PR
{
	class OperatorsFactory
	{	
		OperatorsFactory();
		static OperatorsFactory * instance;
		unordered_map<string, function<shared_ptr<Token>(void)>>  operators;
	public:

		OperatorsFactory & operator = (const OperatorsFactory &) = delete;
		OperatorsFactory(const OperatorsFactory &) = delete;
		~OperatorsFactory();

		static shared_ptr<Token> get(const string &name);
	};

}
