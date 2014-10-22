#include "stdafx.h"
#include "CodeGenerator.h"


namespace PR
{
	CodeGenerator::CodeGenerator()
	{
	}

	CodeGenerator::CodeGenerator(const string &code_str)
		:lexicalAnalyzer(code_str)
	{
		loadAndSetIp();
	}

	CodeGenerator::CodeGenerator(FileLoader &file)
		:lexicalAnalyzer(file.loadAll())
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
		lexicalAnalyzer.setInput(name);
		loadAndSetIp();
	}

	void CodeGenerator::setInput(string &&in)
	{
		lexicalAnalyzer.setInput(std::move(in));
		loadAndSetIp();
	}

	void CodeGenerator::setInput(FileLoader &in)
	{
		lexicalAnalyzer.setInput(in);
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
		if (end && ip==code.end())
			return true;

		if (ip == code.end())
			load();

		return ip == code.end();
	}

	void CodeGenerator::load(void)
	{
		Parser parser(lexicalAnalyzer);
		end = !parser.parse();
		ip = code.insert(code.end(), std::move(parser.getInstruction()));
		lp = code.size() - 1;
	}

}