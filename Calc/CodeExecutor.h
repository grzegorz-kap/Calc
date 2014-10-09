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
		~CodeExecutor();
	

		unique_ptr<Data> run(const Instruction &tokens);

	private:
		vector<unique_ptr<Data>> stack;
		Instruction::const_iterator i;

		vector<unique_ptr<Data>>::iterator find(TOKEN_CLASS _class,bool ex=false);

		void onOperator();
		void onMatrixStart();
		void onMatrixVerseEnd();
		void onMatrixEnd();
		
		void onFunction();


		unique_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);
	};
}

