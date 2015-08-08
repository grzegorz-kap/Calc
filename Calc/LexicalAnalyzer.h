#pragma once

#include <queue>
#include <vector>

using std::vector;
using std::queue;

#include "Token.h"
#include "RegexTokenizer.h"
#include "functions.h"
#include "CalcException.h"
#include "LexicalBalanceHelper.h"
#include "functions.h"
#include "FileLoader.h"

namespace KLab
{
	//! Klasa stanawiaca modul analizy leksykalnej.
	class LexicalAnalyzer
	{
		vector<unique_ptr<Token>> tokens;
		vector<unique_ptr<Token>>::iterator iter;
	public:
		LexicalAnalyzer();
		//! \param tekst wejsciowy.
		LexicalAnalyzer(const string &command);
		~LexicalAnalyzer();

		//! Ustawia wejscie analizatora.
		//! \param commend tekst, ktory zostanie podzielony na tokeny.
		void setInput(const string &command);
		void setInput(string &&in);
		void setInput(FileLoader &in);

		//! Pobranie wodrebnionych symboli leksykalnych.
		auto getTokens() -> decltype(tokens);

	private:
		RegexTokenizer tokenizer;
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

		/*
			Recognize what means (last index of or if/for/while end)
			*/
		void onEndKeyword(Token &token);
	};
}
