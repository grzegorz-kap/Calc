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


namespace PR
{
	class CALC_API LexicalAnalyzer
	{

	public:
		bool hasNext();
		Token getNext();
		TOKEN_CLASS whatNext();

		void setInput(const string &command);

		LexicalAnalyzer();
		LexicalAnalyzer(const string &command);
		~LexicalAnalyzer();

	private:
		Tokenizer tokenizer;
		queue<Token> q;
		bool what_next_flag;
		unsigned int prev_operator_args_num;
		const static vector<TOKEN_CLASS> UNARY_OP_PRECURSORS;

		void reset();
		void push(Token token);
		LexicalBalanceHelper balancer;
		TOKEN_CLASS prev;
		void read();

		void onOperator(Token &token);
		void onComma(Token &token);
		void onSpace(Token &token);
	};
}

