#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

#include "CalcException.h"
#include "Token.h"
namespace PR
{
	class Assignment :
		public Token
	{
		vector<shared_ptr<Token>> target;
	public:
		Assignment();
		~Assignment();

		void loadTarget(vector<shared_ptr<Token>> &vec);
		vector<shared_ptr<Token>>& getTarget();
		virtual Assignment * castToAssignment() override;
	};

}
