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

#include "Token.h"
#include "SNumber.h"
#include "AssignmentFactory.h"
#include "Operator.h"
#include "functions.h"
#include "CalcException.h"
#include "LexicalAnalyzer.h"

namespace PR
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
	public:
		Parser();
		Parser(LexicalAnalyzer &lex);
		~Parser();
		virtual bool parse();
		void setInput(LexicalAnalyzer &lex);
		vector<shared_ptr<Token>> & getInstruction(){ return onp; }
	private:
		TOKEN_CLASS stackBack() const;
		TOKEN_CLASS onpBack() const;
		void stackToOnp();
		void stackToOnpAll();

		TOKEN_CLASS whatNext()
		{
			if (iter + 1 == tokens.end())
				return TOKEN_CLASS::NONE;
			return (*(iter + 1))->getClass();
		}

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
		bool onColon();
		void changeIfAssignment();

		void stackToOnpUntilToken(TOKEN_CLASS type, bool remove = true);
	};
}



#endif