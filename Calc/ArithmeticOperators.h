#pragma once
#include "Operator.h"

namespace PR
{
	class AdditionOperator : public Operator
	{
	public:
		AdditionOperator();
		~AdditionOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class UPlusOperator : public Operator
	{
	public:
		UPlusOperator();
		~UPlusOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class SubtractionOperator : public Operator
	{
	public:
		SubtractionOperator();
		~SubtractionOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class USubtractionOperator : public Operator
	{
	public:
		USubtractionOperator();
		~USubtractionOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class DivisionOperator : public Operator
	{
	public:
		DivisionOperator();
		~DivisionOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class LeftDivisionOperator : public Operator
	{
	public:
		LeftDivisionOperator();
		~LeftDivisionOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class LeftArrayDivision : public Operator
	{
	public:
		LeftArrayDivision();
		~LeftArrayDivision();
		virtual shared_ptr<Data> evaluate() override;
	};

	class RightArrayDivision : public Operator
	{
	public:
		RightArrayDivision();
		~RightArrayDivision();
		virtual shared_ptr<Data> evaluate() override;
	};

	class MultiplicationOperator : public Operator
	{
	public:
		MultiplicationOperator();
		~MultiplicationOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class ElementWiseMultiplication : public Operator
	{
	public:
		ElementWiseMultiplication();
		~ElementWiseMultiplication();
		virtual shared_ptr<Data> evaluate() override;
	};

	class ExponentiationOperator : public Operator
	{
	public:
		ExponentiationOperator();
		~ExponentiationOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class MatrixExponentiationOperator : public Operator
	{
	public:
		MatrixExponentiationOperator();
		~MatrixExponentiationOperator();
		virtual shared_ptr<Data> evaluate() override;
	};
}