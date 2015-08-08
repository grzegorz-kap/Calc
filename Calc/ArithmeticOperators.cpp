#include "stdafx.h"
#include "ArithmeticOperators.h"

namespace PR
{
	AdditionOperator::AdditionOperator()
		:Operator("+", 50, 2, EVAULATED::RIGHT)
	{
	}
	AdditionOperator::~AdditionOperator()
	{
	}
	shared_ptr<Data> AdditionOperator::evaluate()
	{
		return *arguments[0] + arguments[1];
	}

	UPlusOperator::UPlusOperator()
		:Operator("$+", 30, 1, EVAULATED::LEFT)
	{
	}
	UPlusOperator::~UPlusOperator()
	{
	}
	shared_ptr<Data> UPlusOperator::evaluate()
	{
		return std::move(arguments[0]);
	}

	SubtractionOperator::SubtractionOperator()
		:Operator("-", 50, 2, EVAULATED::RIGHT)
	{
	}
	SubtractionOperator::~SubtractionOperator()
	{
	}
	shared_ptr<Data> SubtractionOperator::evaluate()
	{
		return *arguments[0] - arguments[1];
	}

	USubtractionOperator::USubtractionOperator()
		:Operator("$-", 30, 1, EVAULATED::LEFT)
	{
	}
	USubtractionOperator::~USubtractionOperator()
	{
	}
	shared_ptr<Data> USubtractionOperator::evaluate()
	{
		return -*arguments[0];
	}

	DivisionOperator::DivisionOperator()
		:Operator("/", 40, 2, EVAULATED::RIGHT)
	{
	}
	DivisionOperator::~DivisionOperator()
	{
	}
	shared_ptr<Data> DivisionOperator::evaluate()
	{
		return *arguments[0] / arguments[1];
	}

	LeftDivisionOperator::LeftDivisionOperator()
		:Operator("\\", 40, 2, EVAULATED::RIGHT)
	{
	}
	LeftDivisionOperator::~LeftDivisionOperator()
	{
	}
	shared_ptr<Data> LeftDivisionOperator::evaluate()
	{
		if (arguments[0]->isScalar() || arguments[1]->isScalar())
			return *arguments[1] / arguments[0];
		else
			return arguments[0]->url(arguments[1]);
	}

	LeftArrayDivision::LeftArrayDivision()
		:Operator(".\\", 40, 2, EVAULATED::RIGHT)
	{
	}
	LeftArrayDivision::~LeftArrayDivision()
	{
	}
	shared_ptr<Data> LeftArrayDivision::evaluate()
	{
		return arguments[1]->rdivide(arguments[0]);
	}

	RightArrayDivision::RightArrayDivision()
		:Operator("./", 40, 2, EVAULATED::RIGHT)
	{
	}

	RightArrayDivision::~RightArrayDivision()
	{
	}
	shared_ptr<Data> RightArrayDivision::evaluate()
	{
		return arguments[0]->rdivide(arguments[1]);
	}

	MultiplicationOperator::MultiplicationOperator()
		:Operator("*", 40, 2, EVAULATED::RIGHT)
	{
	}
	MultiplicationOperator::~MultiplicationOperator()
	{
	}
	shared_ptr<Data> MultiplicationOperator::evaluate()
	{
		return *arguments[0] * arguments[1];
	}

	ElementWiseMultiplication::ElementWiseMultiplication()
		:Operator(".*", 40, 2, EVAULATED::RIGHT)
	{
	}
	ElementWiseMultiplication::~ElementWiseMultiplication()
	{
	}
	shared_ptr<Data> ElementWiseMultiplication::evaluate()
	{
		return arguments[0]->times(arguments[1]);
	}

	ExponentiationOperator::ExponentiationOperator()
		:Operator(".^", 20, 2, EVAULATED::RIGHT)
	{
	}
	ExponentiationOperator::~ExponentiationOperator()
	{
	}
	shared_ptr<Data> ExponentiationOperator::evaluate()
	{
		return arguments[0]->exponentiation(arguments[1]);
	}

	MatrixExponentiationOperator::MatrixExponentiationOperator()
		:Operator("^", 20, 2, EVAULATED::RIGHT)
	{
	}
	MatrixExponentiationOperator::~MatrixExponentiationOperator()
	{
	}
	shared_ptr<Data> MatrixExponentiationOperator::evaluate()
	{
		return arguments[0]->mexponentiation(arguments[1]);
	}
}