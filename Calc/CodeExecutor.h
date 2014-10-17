#pragma once

#include <memory>
#include <vector>
#include <map>

using std::map;
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
	typedef map<string, shared_ptr<Data>> variables;

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
		
		/* Should not be used directly! */
		variables internal_vars;
		variables &vars_ref;

		shared_ptr<Data> run();
		vector<shared_ptr<Data>>::iterator find(TOKEN_CLASS _class,bool ex=false);
		void onOperator();
		void onMatrixEnd();
		void onFunction();
		void onAssignment();
		
		shared_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);
		bool isKeyword(TOKEN_CLASS _class);
		void setIPTo(const vector<TOKEN_CLASS> &set,int balance);

		void onIF();
		bool checkIF();
		bool checkWhile();

		void next()
		{
			code.inc();
			ip = code.getInstruction();
		}

		void prev()
		{
			code.dec();
			ip = code.getInstruction();
		}

		static const vector<TOKEN_CLASS> IF_FIND;
		static const vector<TOKEN_CLASS> ELSE_FIND;
		static const vector<TOKEN_CLASS> WHILE_FIND;
	};
}

