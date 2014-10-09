#pragma once

#include <memory>
#include <string>
#include <map>
#include <functional>

using std::unique_ptr;
using std::make_unique;
using std::string;
using std::map;
using std::function;

#include "Token.h"
#include "CompareLength.h"
#include "AdditionOperator.h"
#include "SubtractionOperator.h"
#include "MultiplicationOperator.h"
#include "DivisionOperator.h"

namespace PR
{
	class OperatorsFactory
	{	
	private:
		OperatorsFactory();
		static OperatorsFactory * instance;
		map<string, function<unique_ptr<Operator>(void)>,CompareLength>  operators;
	
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
