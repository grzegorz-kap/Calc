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
#include "Operator.h"
#include "OperatorsFactory.h"
#include "NumberReader.h"

namespace PR
{
	class Tokenizer
	{
		static const unordered_map<string, TOKEN_CLASS> KEYWORDS;
	public:
		Tokenizer();
		~Tokenizer();
		
		/**
		Return true if there are symbols to read
		*/
		bool hasNext();

		/**
		Return next symbol in input stream
		*/
		unique_ptr<Token> getNext();
		
		void setInput(const string &command);
		void setInput(string &&command);
 		const static vector<TOKEN_CLASS> FOR_SPACE_DELETE;
		Tokenizer & operator = (Tokenizer &&b);
	private:
		string command;
		int i;
		int N;
		TOKEN_CLASS prev;
		unique_ptr<SNumber> readNumber();
		unique_ptr<Token> readWord();
		unique_ptr<Token> readWhiteSpace();
		unique_ptr<Token> readOthers();
		unique_ptr<Operator> readOperator();
		void skipBlockComment();
		void skipLineComment();
		void readString();
		void whiteSpacesBegin();
		void whiteSpacesEnd();
		void deleteUneccessary();
		
		void init()
		{
			N = command.size();
			i = 0;
			whiteSpacesEnd();
			whiteSpacesBegin();
		}
	
	};

}
