#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

using std::unordered_map;
using std::unique_ptr;
using std::make_unique;
using std::string;
using std::vector;

#include "CalcException.h"
#include "export.h"
#include "functions.h"
#include "Token.h"
#include "SNumber.h"
#include "String.h"
#include "Operator.h"
#include "OperatorsFactory.h"
#include "NumberReader.h"

namespace PR
{
	class Tokenizer
	{
	public:	
		const static vector<TOKEN_CLASS> FOR_SPACE_DELETE;
		
		Tokenizer();
		~Tokenizer();	
		void setInput(const string &command);
		void setInput(string &&command);
		Tokenizer & operator = (Tokenizer &&b);
		void tokenize();
		vector<unique_ptr<Token>> getTokens();

	private:
		static const unordered_map<string, TOKEN_CLASS> KEYWORDS;
		static const vector<string> END_SYNONIMS;
		vector<unique_ptr<Token>> tokens;
		string command;
		int i;
		int N;

		void readNumber();
		void readWord();
		void readWhiteSpace();
		void readOthers();
		bool readOperator();
		void skipBlockComment();
		void skipLineComment();
		void readString();
		void whiteSpacesBegin();
		void whiteSpacesEnd();
		void deleteUneccessary();
		TOKEN_CLASS prev();
		void init();
	};

}
