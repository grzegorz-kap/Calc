#pragma once

#include <string>
#include <vector>

#include "Token.h"
#include "InterpreterContext.h"
#include "export.h"
#include "functions.h"
#include "Operator.h"

#include "NumberReader.h"

namespace PR
{
	using std::string;
	using std::vector;

	class CALC_API Tokenizer
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
		Token getNext();
		
		void setInput(const string &command);
		bool setInputFileName(const string &fileName);
		const static vector<TOKEN_CLASS> FOR_SPACE_DELETE;
	private:
		string command;
		int i;
		int N;
		TOKEN_CLASS prev;
		
		

		Token readNumber();
		Token readWord();
		Token readWhiteSpace();
		bool readOperator(Token &t);
		void skipBlockComment();
		void skipLineComment();
		Token readOthers();
		void readString();
		void whiteSpacesBegin();
		void whiteSpacesEnd();
		void deleteUneccessary();
	
	};

}
