#pragma once

#include <memory>
#include <string>

using std::unique_ptr;
using std::make_unique;
using std::string;

#include "i_order_map.h"
#include "Token.h"
#include "ArithmeticOperators.h"
#include "RelationalOperators.h"
#include "LogicalOperators.h"
#include "AssignmentOperator.h"
#include "TranspositionOperator.h"
#include "Colon2Operator.h"
#include "Colon3Operator.h"


namespace PR
{
	class OperatorsFactory
	{	
	private:
		OperatorsFactory();
		static OperatorsFactory * instance;
		i_order_map<string, unique_ptr<Operator>(*)()>  operators;
	
	public:
		OperatorsFactory & operator = (const OperatorsFactory &) = delete;
		OperatorsFactory(const OperatorsFactory &) = delete;
		~OperatorsFactory();

		static unique_ptr<Operator> get(const string &name,int startIdx,int &length);
		static unique_ptr<Operator> simple_get(const string &name);

	private:
		static void init();
	};

}
