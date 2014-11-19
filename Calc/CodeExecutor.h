#ifndef CODE_EXECUTOR_H
#define CODE_EXECUTOR_H

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
#include "TokensTypes.h"
#include "FunctionFactory.h"
#include "MatrixBuilderFactory.h"
#include "ExternalFunction.h"
#include "SignalEmitter.h"
#include "TypePromotor.h"
#include "Variables.h"
#include "ForIterator.h"

namespace PR
{
	class CodeExecutor
	{
	public:
		CodeExecutor();
		CodeExecutor(Variables &ref);
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
		
		static void set_stop_computing() { stop_computing = true; }
		static void off_stop_computing(){ stop_computing = false; }

		static int recursions;
		static int recursion_limit;

		static vector<shared_ptr<Data>> run_single(const vector<shared_ptr<Token>> &onp, Variables &vars);
	private:

		static bool stop_computing;
		vector<shared_ptr<Data>> stack;
		Instruction::const_iterator i;
		vector<int> conditions;
		vector<int> jumbs;
		vector<ForIterator> for_iterators;
		Ip ip;
		CodeGenerator code;
		bool output_off_flag;
		bool assignment_flag;
		vector<std::pair<std::map<string, shared_ptr<Data>>::iterator, bool>> assignment;

		/* Should not be used directly! */
		Variables internal_vars;
		/* ============================ */

		Variables &vars_ref;
		static Variables globals;

		CodeExecutor(const ExternalFunction &fun, const vector<shared_ptr<Data>> &args);
		vector<shared_ptr<Data>>::iterator find(TOKEN_CLASS _class, bool ex = false);

		shared_ptr<Data> run();
		

		void onOperator();
		void onShortCircuitJumper();
		void onMatrixEnd();

		void onFunction();
		void onMatrixAll();
		void onFunctionArgs();

		
		void onVariableFunction(vector<shared_ptr<Data>> &args, shared_ptr<Data> &var);
		void onExternalFunction(const vector<shared_ptr<Data>> &args, const string &name);

		void onAssignment();
		void defaultAssignment();
		
		void onIF();
		bool checkIF();
		void onWHILE();
		void onWhileEnd();
		bool checkWhile();
		
		bool checkFor();
		void onForKeyword();
		void onForEndKeyword();
		
		void onID();
		bool onScript();

		shared_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);
		bool isKeyword(TOKEN_CLASS _class);
		void setIPTo(const vector<TOKEN_CLASS> &set, int balance);
		void next(){ code.inc();	ip = code.get(); }
		void prev(){ code.dec();	ip = code.get(); }

		static const vector<TOKEN_CLASS> IF_FIND;
		static const vector<TOKEN_CLASS> ELSE_FIND;
		static const vector<TOKEN_CLASS> WHILE_FIND;
		static const vector<TOKEN_CLASS> FOR_FIND;

	};
}


#endif
