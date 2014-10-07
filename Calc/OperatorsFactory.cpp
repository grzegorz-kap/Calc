#include "stdafx.h"
#include "OperatorsFactory.h"


namespace PR
{
	OperatorsFactory * OperatorsFactory::instance = nullptr;

	OperatorsFactory::OperatorsFactory()
	{
		operators["+"] = [](){return shared_ptr<Token>(new PlusOperator()); };

	}

	shared_ptr<Token> OperatorsFactory::get(const string &name)
	{
		if (OperatorsFactory::instance == nullptr)
			instance = new OperatorsFactory();

		return (instance->operators.at(name))();
	}

	OperatorsFactory::~OperatorsFactory()
	{

	}
}
