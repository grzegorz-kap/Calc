#pragma once

#include <queue>
#include <vector>
#include <boost/scoped_ptr.hpp>

using std::vector;
using std::queue;

#include "Token.h"
#include "TokenizerService.h"
#include "functions.h"
#include "CalcException.h"
#include "LexicalBalanceHelper.h"
#include "functions.h"
#include "FileLoader.h"

namespace KLab
{
	class LexicalAnalyzer {
		vector<unique_ptr<Token>> tokens;
		vector<unique_ptr<Token>>::iterator iter;
	public:
		LexicalAnalyzer();
		LexicalAnalyzer(const string &command);
		~LexicalAnalyzer();

		void setInput(const string &command);
		void setInput(string &&in);
		void setInput(FileLoader &in);
		auto getTokens() -> decltype(tokens);

	private:
		boost::scoped_ptr<TokenizerService> tokenizer;
		LexicalBalanceHelper balancer;
		TOKEN_CLASS prev;
		unsigned int prev_operator_args_num;
		const static vector<TOKEN_CLASS> UNARY_OP_PRECURSORS;
		bool for_delete;
		EVAULATED ev_op_prev;

		TOKEN_CLASS whatNext();
		void reset();
		void process(unique_ptr<Token> &token);
		void onOperator(unique_ptr<Token> &token);
		void onComma(Token &token);
		void onSpace(Token &token);
		void onColon(Token &token);
		void onID(Token &token);
		void onEndKeyword(Token &token);
	};
}
