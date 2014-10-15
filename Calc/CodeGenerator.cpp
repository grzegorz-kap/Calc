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