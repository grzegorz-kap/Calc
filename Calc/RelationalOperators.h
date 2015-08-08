#pragma once
#include "Operator.h"

namespace PR
{
	class EqOperator : public Operator
	{
	public:
		EqOperator();
		~EqOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class GeOperator : public Operator
	{
	public:
		GeOperator();
		~GeOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class GtOperator : public Operator
	{
	public:
		GtOperator();
		~GtOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class LeOperator : public Operator
	{
	public:
		LeOperator();
		~LeOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class LTOperator : public Operator
	{
	public:
		LTOperator();
		~LTOperator();
		virtual shared_ptr<Data> evaluate() override;
	};

	class NeOperator : public Operator
	{
	public:
		NeOperator();
		~NeOperator();
		virtual shared_ptr<Data> evaluate() override;
	};
}