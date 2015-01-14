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
		bool eval_flag;						/* eval function flag */
		vector<shared_ptr<Data>> stack;		/* Data stack */
		Instruction::const_iterator i;		/* Single instruction iterator */
		vector<int> conditions;				/* Conditions addresses for while instruction */
		vector<int> jumbs;					/* Jump addresses for while instruction */
		vector<ForIterator> for_iterators;	/* For loop iterators */
		Ip ip;								/* Iterator for code */
		CodeGenerator code;					/* Code storage class */
		bool output_off_flag;				/* Indicates if display data to screen */
		bool assignment_flag;				/* Indicates if assignment occurred, if not default assignment */
		bool _single_run;					/* Single expression computation flag */
		bool _single_id_flag;					/* Should only display variable without assignment */
		AssignmentsData assignment;			/* Storage information of occurred assignments*/
		Variables internal_vars;			/* Should not be used directly! Local variables in extern function execution */
		Variables &vars_ref;				/* Reference to variables */
		static Variables globals;			/* Global variables */
		string _file;						/* File name in casue of script or external function computation */

		/* Constructor for external function execution */
		CodeExecutor(const ExternalFunction &fun, const vector<shared_ptr<Data>> &args);
		
		/* Find specific element in data stack */
		vector<shared_ptr<Data>>::iterator find(TOKEN_CLASS _class, bool ex = false);

		/* Execute single instruction */
		shared_ptr<Data> run(bool multi=true);
		void start(const string &in);

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
		void onEval(vector<shared_ptr<Data>> &args);
		void onElseIf();
		bool checkIF();
		void onWHILE();
		void onWhileEnd();
		bool checkWhile();
		bool checkFor();
		void onForKeyword();
		void onForEndKeyword();
		void onBreakKeyword();
		void onContinueKeyword();
		bool checkLoopsControl();
		void onMatrixAllOrLastInex();
		void onVariablesManagement();
		void loadFromFile(vector<shared_ptr<Data>> &args);
		void onID();
		bool onScript();
		shared_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);
		bool isKeyword(TOKEN_CLASS _class);
		void setIPTo(const vector<TOKEN_CLASS> &set, int balance);
		void next();
		void prev();
		void throwError(const string &name,string src="");
		static const vector<TOKEN_CLASS> IF_FIND;
		static const vector<TOKEN_CLASS> ELSE_FIND;
		static const vector<TOKEN_CLASS> WHILE_FIND;
		static const vector<TOKEN_CLASS> FOR_FIND;
		static const vector<TOKEN_CLASS> ELSEIF_FIND;
		static const vector<TOKEN_CLASS> BRK_CONT_FIND;
	};
}


#endif
