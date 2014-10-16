#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;


#include "Token.h"
namespace PR
{
	class Assignment :
		public Token
	{
		vector<unique_ptr<Token>> target;
	public:
		Assignment();
		~Assignment();

		void loadTarget(vector<unique_ptr<Token>> &vec);
	};

}
