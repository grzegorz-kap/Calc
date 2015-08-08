#ifndef PARSER_H
#define PARSER_H

#pragma once

#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::dynamic_pointer_cast;

#include "Token.h"
#include "ShortCircuitJumper.h"
#include "SNumber.h"
#include "AssignmentFactory.h"
#include "Operator.h"
#include "functions.h"
#include "CalcException.h"
#include "LexicalAnalyzer.h"
#include "InstructionFor.h"

namespace KLab
{
	class Parser
	{
	private:
		vector<shared_ptr<Token>> onp;
		vector<shared_ptr<Token>> stack;
		bool stop;
		unique_ptr<Token> i;
		vector<unique_ptr<Token>> tokens;
		vector<unique_ptr<Token>>::iterator iter;
		vector<TYPE> _ev_type_mode;
		vector<int>  _ev_type_balance;
		vector<string> _function_names;
		vector<int> _function_args;
		vector<vector<int>> _function_onp_addr;
		string _file;
	public:

		Parser();
		Parser(LexicalAnalyzer &lex);
		~Parser();
		virtual bool parse();
		void setInput(LexicalAnalyzer &lex, string fileInfo);
		vector<shared_ptr<Token>> & getInstruction();
		void setFileInfo(const string &name);

	private:
		TOKEN_CLASS stackBack() const;
		TOKEN_CLASS onpBack() const;
		void stackToOnp();
		void stackToOnpAll();
		void iterBack();
		TOKEN_CLASS whatNext();

		void onKeywordFOR();
		void onKeywords();
		void onDefault();
		void onID();
		void onNumber();
		void onOpenParenthesis();
		void onCloseParenthesis();
		void onMatrixStart();
		void onMatrixAll();
		void onMatrixEnd();
		void onNewLine();
		void onFunction();
		void onOperator();
		void onComma();
		void onSemicolon();
		void onColon();
		void changeIfAssignment();
		void onShortCircuitOperator();
		void computeTreeLevels();
		void stackToOnpUntilToken(TOKEN_CLASS type, bool remove = true);
		static void computeShortCircuitJumps(vector<shared_ptr<Token>> &onp);

		void throwException(const string &message);
	};
}

#endif