#pragma once

#include "export.h"
#include "CalcException.h"

#include <string>
#include <vector>
#include <algorithm>
#include "Token.h"

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
		int arguments;
		EVAULATED ev;

	public:
		//static const vector<Operator> OPERATORS;
		Operator(const string &name, int priority, int arguments,EVAULATED ev);
		~Operator();
		bool operator < (const Operator &b) const;
		int getPriority() const { return priority; }
		int getArguments() const { return arguments; }
		EVAULATED getEv() const { return ev; }

		virtual Operator * castToOperator()  override
		{
			return dynamic_cast<Operator *>(this);
		}
	};

}


