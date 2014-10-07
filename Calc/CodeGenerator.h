#pragma once

#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::string;
using std::shared_ptr;

#include "declarations.h"
#include "Token.h"
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "CodeGeneratorException.h"

namespace PR
{
	class CodeGenerator
	{
		
	private:
		CODE code;
		CODE::iterator ip;
		LexicalAnalyzer lexicalAnalyzer;
		bool end;
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