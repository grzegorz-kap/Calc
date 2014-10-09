#pragma once

#include <string>
#include <vector>
#include <memory>

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
		bool setInputFileName(const string &fileName);
 		const static vector<TOKEN_CLASS> FOR_SPACE_DELETE;

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
	
	};

}
