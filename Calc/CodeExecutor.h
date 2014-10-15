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
		int balance;

		shared_ptr<Data> run();
		vector<shared_ptr<Data>>::iterator find(TOKEN_CLASS _class,bool ex=false);
		void onOperator();
		void onMatrixEnd();
		void onFunction();
		void onIF();
		shared_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);
		bool isKeyword(TOKEN_CLASS _class);
		void setIPTo(const vector<TOKEN_CLASS> &set);

		void next(bool check=false)
		{
			code.inc();

			if (check && code.eof())
				return;

			ip = code.getInstruction();
		}

		void balance_down()
		{
			if (--balance < 0)
				throw CalcException("Unbalanced");
		}

		void balance_up();

		static const vector<TOKEN_CLASS> IF_FIND;
	};
}

