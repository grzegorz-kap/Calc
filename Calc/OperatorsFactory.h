#pragma once

#include <memory>
#include <string>

using std::unique_ptr;
using std::make_unique;
using std::string;

#include "i_order_map.h"
#include "Token.h"
#include "AdditionOperator.h"
#include "SubtractionOperator.h"
#include "USubtractionOperator.h"
#include "MultiplicationOperator.h"
#include "ElementWiseMultiplication.h"
#include "DivisionOperator.h"
#include "RightArrayDivision.h"
#include "LeftArrayDivision.h"
#include "ExponentiationOperator.h"
#include "MatrixExponentiationOperator.h"
#include "EqOperator.h"
#include "GeOperator.h"
#include "Gt.h"
#include "LeOperator.h"
#include "LTOperator.h"
#include "NeOperator.h"
#include "AssignmentOperator.h"
#include "TranspositionOperator.h"
#include "UPlusOperator.h"
#include "Colon2Operator.h"
#include "Colon3Operator.h"
#include "AndOperator.h"
#include "OROperator.h"
#include "ElementWiseAnd.h"
#include "ElementWiseOr.h"
#include "LogicalNotOperator.h"

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

		static unique_ptr<Operator> get(const string &name,int startIdx=0);
		static unique_ptr<Operator> simple_get(const string &name);

	private:
		static void init();
	};

}
