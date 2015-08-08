#include "stdafx.h"
#include "OperatorsFactory.h"

namespace PR
{
	extern template class i_order_map < string, unique_ptr<Operator>(*)(void) > ;

	OperatorsFactory * OperatorsFactory::instance = nullptr;

	OperatorsFactory::OperatorsFactory()
	{
		/* Order metters! */
		operators.insert("==", []()->unique_ptr < Operator > {return make_unique<EqOperator>(); });
		operators.insert("~=", []()->unique_ptr < Operator > {return make_unique<NeOperator>(); });
		operators.insert("<=", []()->unique_ptr < Operator > {return make_unique<LeOperator>(); });
		operators.insert(">=", []()->unique_ptr < Operator > {return make_unique<GeOperator>(); });
		operators.insert("<", []()->unique_ptr < Operator > {return make_unique<LTOperator>(); });
		operators.insert(">", []()->unique_ptr < Operator > {return make_unique<GtOperator>(); });
		operators.insert("$-", []()->unique_ptr < Operator > {return make_unique<USubtractionOperator>(); });
		operators.insert("$+", []()->unique_ptr < Operator > {return make_unique <UPlusOperator>(); });
		operators.insert(".+", []()->unique_ptr < Operator > {return make_unique<AdditionOperator>(); });
		operators.insert(".-", []()->unique_ptr < Operator > {return make_unique<SubtractionOperator>(); });
		operators.insert("+", []()->unique_ptr < Operator > {return make_unique<AdditionOperator>(); });
		operators.insert("-", []()->unique_ptr < Operator > {return make_unique<SubtractionOperator>(); });
		operators.insert(".*", []()->unique_ptr < Operator > {return make_unique<ElementWiseMultiplication>(); });
		operators.insert("*", []()->unique_ptr < Operator > {return make_unique<MultiplicationOperator>(); });
		operators.insert("./", []()->unique_ptr < Operator > {return make_unique<RightArrayDivision>(); });
		operators.insert(".\\", []()->unique_ptr < Operator > {return make_unique<LeftArrayDivision>(); });
		operators.insert("\\", []()->unique_ptr < Operator > {return make_unique<LeftDivisionOperator>(); });
		operators.insert("/", []()->unique_ptr < Operator > {return make_unique<DivisionOperator>(); });
		operators.insert(".^", []()->unique_ptr < Operator > {return make_unique<ExponentiationOperator>(); });
		operators.insert("^", []()->unique_ptr < Operator > {return make_unique<MatrixExponentiationOperator>(); });
		operators.insert("=", []()->unique_ptr < Operator > {return make_unique<AssignmentOperator>(); });
		operators.insert(".'", []()->unique_ptr < Operator > {return make_unique<TranspositionOperator>(); });
		operators.insert("'", []()->unique_ptr < Operator > {return make_unique<ConjugateTranspositionOperator>(); });
		operators.insert("&&", []()->unique_ptr < Operator > {return make_unique<AndOperator>(); });
		operators.insert("||", []()->unique_ptr < Operator > {return make_unique<OROperator>(); });
		operators.insert("|", []()->unique_ptr < Operator > {return make_unique<ElementWiseOr>(); });
		operators.insert("&", []()->unique_ptr < Operator > {return make_unique<ElementWiseAnd>(); });
		operators.insert("~", []()->unique_ptr < Operator > {return make_unique<LogicalNotOperator>(); });
	}

	void OperatorsFactory::init()
	{
		if (OperatorsFactory::instance == nullptr)
			instance = new OperatorsFactory();
	}

	unique_ptr<Operator> OperatorsFactory::get(const string &name, int startIdx, int &length)
	{
		init();
		length = 0;
		const vector<string> &vec = instance->operators.getVec();
		for (auto iter = vec.cbegin(); iter != vec.cend(); iter++)
		{
			if (!name.compare(startIdx, iter->length(), *iter))
			{
				length = iter->length();
				return instance->operators[*iter]();
			}
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