#include "stdafx.h"
#include "OperatorsFactory.h"


namespace PR
{
	OperatorsFactory * OperatorsFactory::instance = nullptr;

	OperatorsFactory::OperatorsFactory()
	{
		/* Order metters! */
		operators.insert("==", [](){return make_unique<EqOperator>(); });
		operators.insert("~=", [](){return make_unique<NeOperator>(); });
		operators.insert("<=", [](){return make_unique<LeOperator>(); });
		operators.insert(">=", [](){return make_unique<GeOperator>(); });
		operators.insert("<", [](){return make_unique<LTOperator>(); });
		operators.insert(">", [](){return make_unique<Gt>(); });
		operators.insert("+", [](){return make_unique<AdditionOperator>(); });
		operators.insert("-", [](){return make_unique<SubtractionOperator>(); });
		operators.insert(".*", [](){return make_unique<ElementWiseMultiplication>(); });
		operators.insert("*", [](){return make_unique<MultiplicationOperator>(); });
		operators.insert("./", [](){return make_unique<RightArrayDivision>(); });
		operators.insert(".\\", [](){return make_unique<LeftArrayDivision>(); });
		operators.insert("/", [](){return make_unique<DivisionOperator>(); });
		operators.insert(".^", [](){return make_unique<ExponentiationOperator>(); });
		operators.insert("^", [](){return make_unique<MatrixExponentiationOperator>(); });
		operators.insert("$-", [](){return make_unique<USubtractionOperator>(); });
		operators.insert("=", [](){return make_unique<AssignmentOperator>(); });
		operators.insert("'", [](){return make_unique<TranspositionOperator>(); });
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
