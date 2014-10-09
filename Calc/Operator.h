#pragma once

#include "export.h"
#include "CalcException.h"
#include "EvalException.h"
#include "Token.h"
#include "Data.h"

#include <string>
#include <vector>
#include <algorithm>


using std::string;
using std::vector;

namespace PR
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
		vector<unique_ptr<Data>> arguments;
	public:
		Operator(const string &name, int priority, int arguments,EVAULATED ev);
		~Operator();
		bool operator < (const Operator &b) const;
		int getPriority() const { return priority; }
		int getArgumentsNum() const { return argumentsNum; }
		EVAULATED getEv() const { return ev; }

		virtual Operator * castToOperator()  override
		{
			return dynamic_cast<Operator *>(this);
		}

		void setArguments(vector<unique_ptr<Data>> &stack);
	};

}


