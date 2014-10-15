#pragma once

#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

#include "Token.h"
#include "CodeGenerator.h"
#include "CalcException.h"
#include "Operator.h"
#include "MatrixBuilder.h"
#include "MatrixTransposer.h"
#include "TokensTypes.h"
#include "FunctionFactory.h"

namespace PR
{
	class CodeExecutor
	{
	public:
		CodeExecutor();
		CodeExecutor(const string &name);
		CodeExecutor(FileLoader &&file);
		~CodeExecutor();
	
		shared_ptr<Data> run(const Instruction &tokens);

	private:
		vector<shared_ptr<Data>> stack;
		Instruction::const_iterator i;
		CodeGenerator code;

		vector<shared_ptr<Data>>::iterator find(TOKEN_CLASS _class,bool ex=false);
		void onOperator();
		void onMatrixEnd();
		void onFunction();
		shared_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);
	};
}

