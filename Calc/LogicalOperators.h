#pragma once
#include "Operator.h"

namespace KLab
{
	class AndOperator : public Operator
	{
	public:
		AndOperator();
		~AndOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class OROperator : public Operator
	{
	public:
		OROperator();
		~OROperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class ElementWiseAnd : public Operator
	{
	public:
		ElementWiseAnd();
		~ElementWiseAnd();
		virtual shared_ptr<Data> evaluate() override;
	};

	class ElementWiseOr : public Operator
	{
	public:
		ElementWiseOr();
		~ElementWiseOr();
		virtual shared_ptr<Data> evaluate() override;
	};

	class LogicalNotOperator : public Operator
	{
	public:
		LogicalNotOperator();
		~LogicalNotOperator();
		virtual shared_ptr<Data> evaluate() override;
	};
}