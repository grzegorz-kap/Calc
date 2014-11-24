#ifndef CODE_EXECUTOR_H
#define CODE_EXECUTOR_H

#pragma once

#include <memory>
#include <vector>
#include <map>

using std::map;
using std::unique_ptr;
using std::vector;

#include "CodeGenerator.h"
#include "FunctionFactory.h"
#include "ExternalFunction.h"
#include "MatrixBuilderFactory.h"
#include "SignalEmitter.h"
#include "TypePromotor.h"
#include "Variables.h"
#include "ForIterator.h"

namespace PR
{
	class CodeExecutor
	{
		
	public:
		static int recursions;
		static int recursion_limit;

		CodeExecutor();
		CodeExecutor(Variables &ref);
		~CodeExecutor();
		
		void setInput(const string &in);
		void setInput(FileLoader &in);
		void start();	
		static void set_stop_computing();
		static void off_stop_computing();
		static vector<shared_ptr<Data>> run_single(const vector<shared_ptr<Token>> &onp, Variables &vars);
		static bool isMatrixEndOrColon(const shared_ptr<Token> &t);
	private:

		static bool stop_computing;			/* Set to true if compution should be canceled*/
		vector<shared_ptr<Data>> stack;		/* Data stack */
		Instruction::const_iterator i;		/* Single instruction iterator */
		vector<int> conditions;				/* Conditions addresses for while instruction */
		vector<int> jumbs;					/* Jump addresses for while instruction */
		vector<ForIterator> for_iterators;	/* For loop iterators */
		Ip ip;								/* Iterator for code */
		CodeGenerator code;					/* Code storage class */
		bool output_off_flag;				/* Indicates if display data to screen */
		bool assignment_flag;				/* Indicates if assignment occurred, if not default assignment */
		AssignmentsData assignment;			/* Storage information of occurred assignments*/
		Variables internal_vars;			/* Should not be used directly! Local variables in extern function execution */
		Variables &vars_ref;				/* Reference to variables */
		static Variables globals;			/* Global variables */
		bool _single_run;

		/* Constructor for external function execution */
		CodeExecutor(const ExternalFunction &fun, const vector<shared_ptr<Data>> &args);
		
		/* Find specific element in data stack */
		vector<shared_ptr<Data>>::iterator find(TOKEN_CLASS _class, bool ex = false);

		/* Execute single instruction */
		shared_ptr<Data> run();
		

		void onOperator();
		void onShortCircuitJumper();
		void onMatrixEnd();
		void onFunction();
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
		void onMatrixAllOrLastInex();
		void onID();
		bool onScript();
		shared_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);
		bool isKeyword(TOKEN_CLASS _class);
		void setIPTo(const vector<TOKEN_CLASS> &set, int balance);
		void next();
		void prev();
		static const vector<TOKEN_CLASS> IF_FIND;
		static const vector<TOKEN_CLASS> ELSE_FIND;
		static const vector<TOKEN_CLASS> WHILE_FIND;
		static const vector<TOKEN_CLASS> FOR_FIND;
	};
}


#endif
