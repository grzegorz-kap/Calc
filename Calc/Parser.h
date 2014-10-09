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
#include "Operator.h"
#include "functions.h"
#include "CalcException.h"
#include "LexicalAnalyzer.h"

namespace PR
{
	class Parser
	{
	private:
		vector<unique_ptr<Token>> onp;
		vector<unique_ptr<Token>> stack;
		bool stop;
		LexicalAnalyzer& lexAnalyzer;
		Token i;
	public:
		Parser(LexicalAnalyzer &lex);
		~Parser();
		virtual bool parse();

		vector<unique_ptr<Token>> & getInstruction(){ return onp; }
	private:
		
		TOKEN_CLASS stackBack() const;
		TOKEN_CLASS onpBack() const;
		void stackToOnp();
		void stackToOnpAll();

		void onID();
		void onNumber();
		void onOpenParenthesis();
		void onCloseParenthesis();
		void onMatrixStart();
		void onMatrixEnd();
		void onNewLine();
		void onFunction();
		void onOperator();
		void onComma();
		void onSemicolon();
		bool onColon();

		void stackToOnpUntilToken(TOKEN_CLASS type,bool remove=true);
	
	};
}

