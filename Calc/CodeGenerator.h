#pragma once

#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::string;
using std::shared_ptr;

#include "Token.h"
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "CodeGeneratorException.h"
#include "Data.h"

namespace PR
{
	typedef vector<vector<shared_ptr<Token>>> Code;
	typedef vector<shared_ptr<Token>> Instruction;
	typedef Code::iterator Ip;

	class CodeGenerator
	{
		
	private:
		Code code;
		Ip ip;
		bool end;
		LexicalAnalyzer lexicalAnalyzer;

	public:
		CodeGenerator(const string &code_str);
		~CodeGenerator();
		
		bool eof(void);
		auto getInstruction() ->decltype(ip);

		void inc();
		void dec();
		
	private:
		void load(void);
	};


}