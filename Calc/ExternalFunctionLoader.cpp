#include "stdafx.h"
#include "ExternalFunctionLoader.h"


namespace PR
{
	ExternalFunctionLoader::ExternalFunctionLoader(const string &name)
		:code(FileLoader(name+".m")),
		name(name)
	{
		throwEof();
		ip = code.get();
		start();
	}


	ExternalFunctionLoader::~ExternalFunctionLoader()
	{
	}

	void ExternalFunctionLoader::start()
	{
		if (loadSymbol() != TOKEN_CLASS::FUNCTION_KEYWORD)
			throw CalcException("Wrong start of function declaration!");
		next();
		
		i = ip->begin();
		loadOutput();
		checkIfInputArgs();
		loadInput();
		loadName();
		checkFunctionDeclEnd();
		
		code.inc();
		loadBody();
	}

	void ExternalFunctionLoader::loadBody()
	{
		while (!code.eof())
		{
			ip = code.get();
			if (ip->size() == 1 && ip->at(0)->getClass() == TOKEN_CLASS::END_FUNCTION)
				break;
			
			fun.addInstruction(std::move(*ip));

			code.inc();
		}

		if (loadSymbol() != TOKEN_CLASS::END_FUNCTION)
			throw CalcException("Function end not found!");
	}

	void ExternalFunctionLoader::checkFunctionDeclEnd()
	{
		throwEofInstruction();
		if ((*i)->getClass() != TOKEN_CLASS::ASSIGNMENT)
			throw CalcException("Invalid funtion declaration! = not found!");
		i++;
		if (i != ip->end())
			throw CalcException("Instruction end expected but not found!");
	}

	void ExternalFunctionLoader::loadOutput()
	{
		AssignmentMulti* assignment = dynamic_cast<AssignmentMulti *>(i->get());
		if (assignment == nullptr)
			throw CalcException("Output list not found!");
		const auto &target = assignment->getTargetConstReference();
		for (const auto &element : target)
		{
			if (element->_assignment_type != ASSIGNMENT_TYPE::SINGLE)
				throw CalcException("Invalid output list in function " + name, element->getPosition());
			fun.addOutput(element->getLexeme());
		}

		i++;
	}

	void ExternalFunctionLoader::checkIfInputArgs()
	{
		throwEofInstruction();
		if ((*i)->getClass() != TOKEN_CLASS::FUNCTON_ARGS_END)
			throw CalcException("Input arguments declaration not found!");
		i++;
	}

	void ExternalFunctionLoader::loadInput()
	{
		for (; (*i)->getClass() != TOKEN_CLASS::FUNCTION; i++)
		{
			if (i == ip->end())
				throw CalcException("Function name not found!");
			if ((*i)->getClass() != TOKEN_CLASS::ID)
				throw CalcException("Invalid input arguments declaration");
			fun.addInput((*i)->getLexeme());
		}
	}

	void ExternalFunctionLoader::loadName()
	{
		throwEofInstruction();
		if ((*i)->getClass() != TOKEN_CLASS::FUNCTION)
			throw CalcException("Function name not found!");
		if ((*i)->getLexemeR() != name)
			throw CalcException("Function name does not match file name!");
		fun.setName(name);
		i++;
	}

	TOKEN_CLASS ExternalFunctionLoader::loadSymbol()
	{
		throwEof();
		throwSize();
		return ip->at(0)->getClass();
	}

	void ExternalFunctionLoader::throwEof()
	{
		if (code.eof())
			throw CalcException("Unexpected end of code");
	}

	void ExternalFunctionLoader::throwEofInstruction()
	{
		if (i == ip->end())
			throw CalcException("Unexpeceted end of instruction");
	}

	void ExternalFunctionLoader::throwSize(int n)
	{
		if (ip->size() != n)
			throw CalcException("Unexpected type of instruction!");
	}
}
