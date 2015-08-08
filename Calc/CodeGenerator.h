#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#pragma once

#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::string;
using std::shared_ptr;

#include "Parser.h"
#include "FileLoader.h"
#include "CodeGeneratorException.h"

namespace KLab
{
	typedef vector<vector<shared_ptr<Token>>> Code;
	typedef vector<shared_ptr<Token>> Instruction;
	typedef Code::iterator Ip;

	class CodeGenerator
	{
	private:
		Code code;
		Ip ip;
		int lp;
		bool end;
		Parser parser;
	public:
		CodeGenerator();
		CodeGenerator(const string &code_str);
		CodeGenerator(FileLoader &file);
		CodeGenerator(const Code &codeA);
		~CodeGenerator();

		void setInput(const string &in);
		void setInput(string &&in);
		void setInput(FileLoader &file);
		bool eof(void);
		Ip get();
		Ip get(int n);
		int getLP();
		void setIp(int lpA);
		void inc();
		void dec();

	private:
		void load(void);
		void loadAndSetIp();
	};
}

#endif