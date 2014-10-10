#pragma once

#include <memory>
#include <string>
#include <functional>

using std::unique_ptr;
using std::make_unique;
using std::string;
using std::function;

#include "i_order_map.h"
#include "Token.h"
#include "CompareLength.h"
#include "AdditionOperator.h"
#include "SubtractionOperator.h"
#include "MultiplicationOperator.h"
#include "DivisionOperator.h"
#include "ExponentiationOperator.h"

namespace PR
{
	class OperatorsFactory
	{	
	private:
		OperatorsFactory();
		static OperatorsFactory * instance;
		i_order_map<string, function<unique_ptr<Operator>(void)>>  operators;
	
	public:
		OperatorsFactory & operator = (const OperatorsFactory &) = delete;
		OperatorsFactory(const OperatorsFactory &) = delete;
		~OperatorsFactory();

		static unique_ptr<Operator> get(const string &name,int startIdx=0);
		static unique_ptr<Operator> simple_get(const string &name);

	private:
		static void init();
	};

}
