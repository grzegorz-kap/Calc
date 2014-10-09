#include "stdafx.h"
#include "OperatorsFactory.h"


namespace PR
{
	OperatorsFactory * OperatorsFactory::instance = nullptr;

	OperatorsFactory::OperatorsFactory()
	{
		operators.insert("+", [](){return make_unique<AdditionOperator>(); });
		operators.insert("-", [](){return make_unique<SubtractionOperator>(); });
		operators.insert("*", [](){return make_unique<MultiplicationOperator>(); });
		operators.insert("/", [](){return make_unique<DivisionOperator>(); });
	}

	void OperatorsFactory::init()
	{
		if (OperatorsFactory::instance == nullptr)
			instance = new OperatorsFactory();
	}

	unique_ptr<Operator> OperatorsFactory::get(const string &name,int startIdx)
	{
		init();
		const vector<string> &vec = instance->operators.getVec();
		for (auto iter = vec.cbegin(); iter != vec.cend(); iter++)
		{
			if (!name.compare(startIdx, iter->length(), *iter))
				return instance->operators[*iter]();
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
