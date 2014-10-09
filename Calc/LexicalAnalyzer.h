#pragma once

#include <queue>
#include <vector>

using std::vector;
using std::queue;

#include "Token.h"
#include "Tokenizer.h"
#include "functions.h"
#include "CalcException.h"
#include "LexicalBalanceHelper.h"
#include "functions.h"


namespace PR
{
	class LexicalAnalyzer
	{

	public:
		bool hasNext();
		unique_ptr<Token> getNext();
		TOKEN_CLASS whatNext();

		void setInput(const string &command);

		LexicalAnalyzer();
		LexicalAnalyzer(const string &command);
		~LexicalAnalyzer();

	private:
		Tokenizer tokenizer;
		queue<unique_ptr<Token>> q;
		bool what_next_flag;
		unsigned int prev_operator_args_num;
		const static vector<TOKEN_CLASS> UNARY_OP_PRECURSORS;

		void reset();
		void push(unique_ptr<Token> &token);
		LexicalBalanceHelper balancer;
		TOKEN_CLASS prev;
		void read();

		void onOperator(unique_ptr<Token> &token);
		void onComma(Token &token);
		void onSpace(Token &token);
	};
}

