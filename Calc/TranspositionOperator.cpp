#include "stdafx.h"
#include "TranspositionOperator.h"

namespace PR
{
	TranspositionOperator::TranspositionOperator()
		:Operator(".'", 20, 1, EVAULATED::RIGHT)
	{
	}

	TranspositionOperator::~TranspositionOperator()
	{
	}

	shared_ptr<Data> TranspositionOperator::evaluate()
	{
		return arguments[0]->transposition();
	}

	ConjugateTranspositionOperator::ConjugateTranspositionOperator()
		:Operator("'", 20, 1, EVAULATED::RIGHT)
	{
	}

	ConjugateTranspositionOperator::~ConjugateTranspositionOperator()
	{
	}

	shared_ptr<Data> ConjugateTranspositionOperator::evaluate()
	{
		return arguments[0]->ctransposition();
	}
}