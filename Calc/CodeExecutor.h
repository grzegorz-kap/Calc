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
		void setInput(const string &in)
		{
			code.setInput(in);
		};
		void setInput(FileLoader &in)
		{
			code.setInput(in);
		}
		void start();
		

	private:
		vector<shared_ptr<Data>> stack;
		Instruction::const_iterator i;
		Ip ip;
		CodeGenerator code;
		shared_ptr<Data> run(const Instruction &tokens);

		vector<shared_ptr<Data>>::iterator find(TOKEN_CLASS _class,bool ex=false);
		void onOperator();
		void onMatrixEnd();
		void onFunction();
		shared_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);

		bool isKeyword(TOKEN_CLASS _class);
	};
}

