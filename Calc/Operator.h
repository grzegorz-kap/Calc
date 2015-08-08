#pragma once

#include "export.h"
#include "CalcException.h"
#include "EvalException.h"
#include "Token.h"
#include "Data.h"
#include "TypePromotor.h"

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

namespace KLab
{
	enum class EVAULATED :char  {
		LEFT,
		RIGHT
	};

	class  Operator
		: public Token
	{
	protected:
		int priority;
		int argumentsNum;
		EVAULATED ev;
		vector<shared_ptr<Data>> arguments;

		void throwIfNot(const string &message, bool(*fun)(const shared_ptr<Data> &)) const;

	public:
		Operator(const string &name, int priority, int arguments, EVAULATED ev);
		~Operator();
		bool operator < (const Operator &b) const;
		int getPriority() const { return priority; }
		int getArgumentsNum() const { return argumentsNum; }
		void setPriority(int pr){ priority = pr; }
		EVAULATED getEv() const { return ev; }

		virtual Operator * castToOperator()  override
		{
			return dynamic_cast<Operator *>(this);
		}

		void setArguments(vector<shared_ptr<Data>> &stack);
		void clearArguments();
		virtual void promoteArguments();
		void promoteToMatrix();

		virtual bool isColon2Operator() const { return false; }
	};
}
