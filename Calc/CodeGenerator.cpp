#include "stdafx.h"
#include "CodeGenerator.h"


namespace PR
{
	CodeGenerator::CodeGenerator(const string &code_str)
		:lexicalAnalyzer(code_str)
	{
		load();
		ip = code.begin();
	}


	CodeGenerator::~CodeGenerator()
	{
	}

	auto CodeGenerator::getInstruction()
		-> decltype(ip)
	{
		if (eof())
			throw CodeGeneratorException("No instrunction to load");
		return ip;
	}

	void CodeGenerator::dec()
	{
		if (ip == code.begin())
			throw CodeGeneratorException("Begin of code reached!");

		ip--;
	}

	void CodeGenerator::inc()
	{
		if (eof())
			throw CodeGeneratorException("End of code reached!");

		ip++;
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
	}

}