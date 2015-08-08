#include "stdafx.h"
#include "CodeGenerator.h"

namespace KLab
{
	CodeGenerator::CodeGenerator()
	{
	}

	CodeGenerator::CodeGenerator(const string &code_str)
		:parser(LexicalAnalyzer(code_str))
	{
		loadAndSetIp();
	}

	CodeGenerator::CodeGenerator(FileLoader &file)
		: parser(LexicalAnalyzer(file.loadAll()))
	{
		loadAndSetIp();
	}

	CodeGenerator::CodeGenerator(const Code &codeA)
		: code(codeA)
	{
		ip = code.begin();
		lp = 0;
		end = true;
	}

	CodeGenerator::~CodeGenerator()
	{
	}

	void CodeGenerator::setInput(const string &name)
	{
		parser.setInput(LexicalAnalyzer(name), "");
		loadAndSetIp();
	}

	void CodeGenerator::setInput(string &&in)
	{
		parser.setInput(LexicalAnalyzer(in), "");
		loadAndSetIp();
	}

	void CodeGenerator::setInput(FileLoader &in)
	{
		parser.setInput(LexicalAnalyzer(in.loadAll()), in.getFileName());
		loadAndSetIp();
	}

	Ip CodeGenerator::get()
	{
		if (eof())
			throw CodeGeneratorException("No instrunction to load");
		return ip;
	}

	Ip CodeGenerator::get(int a)
	{
		if (eof())
			throw CodeGeneratorException("No instrunction to load");
		return code.begin() + a;
	}

	void CodeGenerator::dec()
	{
		if (ip == code.begin())
			throw CodeGeneratorException("Begin of code reached!");
		lp--;
		ip--;
	}

	void CodeGenerator::inc()
	{
		if (eof())
			throw CodeGeneratorException("End of code reached!");
		ip++;
		lp++;
	}

	bool CodeGenerator::eof()
	{
		if (end && ip == code.end())
			return true;

		if (ip == code.end())
			load();

		return ip == code.end();
	}

	void CodeGenerator::load(void)
	{
		end = !parser.parse();
		ip = code.insert(code.end(), std::move(parser.getInstruction()));
		lp = code.size() - 1;
	}

	int CodeGenerator::getLP()
	{
		return lp;
	}

	void CodeGenerator::setIp(int lpA)
	{
		ip = code.begin() + lpA;
		lp = lpA;
	}

	void CodeGenerator::loadAndSetIp()
	{
		lp = 0;
		load();
		ip = code.begin();
	}
}