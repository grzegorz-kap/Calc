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

namespace PR
{
	typedef map<string, shared_ptr<Data>> variables;

	class CodeExecutor
	{
	public:
		CodeExecutor();
		CodeExecutor(variables &ref);
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
	private:
		static bool stop_computing;
		vector<shared_ptr<Data>> stack;
		Instruction::const_iterator i;
		vector<int> conditions;
		vector<int> jumbs;
		Ip ip;
		CodeGenerator code;
		bool output_off_flag;
		bool assignment_flag;
		vector<std::pair<std::map<string, shared_ptr<Data>>::iterator, bool>> assignment;
		
		/* Should not be used directly! */
		variables internal_vars;
		/* ============================ */

		variables &vars_ref;
		static variables globals;

		CodeExecutor(const ExternalFunction &fun, const vector<shared_ptr<Data>> &args);
		shared_ptr<Data> run();
		vector<shared_ptr<Data>>::iterator find(TOKEN_CLASS _class,bool ex=false);
		
		void onOperator();
		void onMatrixEnd();
		void onFunction();
		void onExternalFunction(const vector<shared_ptr<Data>> &args,const string &name);
		void onAssignment();
		void defaultAssignment();
		void onIF();
		bool checkIF();
		void onWHILE();
		void onWhileEnd();
		bool checkWhile();
		void onID();

		shared_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);
		bool isKeyword(TOKEN_CLASS _class);
		void setIPTo(const vector<TOKEN_CLASS> &set, int balance);
		void next(){ code.inc();	ip = code.get(); }
		void prev(){ code.dec();	ip = code.get(); }

		static const vector<TOKEN_CLASS> IF_FIND;
		static const vector<TOKEN_CLASS> ELSE_FIND;
		static const vector<TOKEN_CLASS> WHILE_FIND;
	};
}

