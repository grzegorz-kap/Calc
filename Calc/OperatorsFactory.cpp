#include "stdafx.h"
#include "OperatorsFactory.h"


namespace PR
{
	OperatorsFactory * OperatorsFactory::instance = nullptr;

	OperatorsFactory::OperatorsFactory()
	{
		operators["+"] = [](){return make_unique<AdditionOperator>(); };
		operators["-"] = [](){return make_unique<SubtractionOperator>(); };
		operators["*"] = [](){return make_unique<MultiplicationOperator>(); };
		operators["/"] = [](){return make_unique<DivisionOperator>(); };
	}

	void OperatorsFactory::init()
	{
		if (OperatorsFactory::instance == nullptr)
			instance = new OperatorsFactory();
	}

	unique_ptr<Operator> OperatorsFactory::get(const string &name,int startIdx)
	{
		init();

		for (auto iter = instance->operators.begin(); iter != instance->operators.end(); iter++)
		{
			if (!name.compare(startIdx, iter->first.length(), iter->first))
				return iter->second();
		}
		return nullptr;
	}

	unique_ptr<Operator> OperatorsFactory::simple_get(const string &name)
	{
		return instance->operators[name]();
	}

	OperatorsFactory::~OperatorsFactory()
	{

	}
}
