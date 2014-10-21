#pragma once

#include "ExternalFunction.h"
#include "CodeGenerator.h"

namespace PR
{
	class ExternalFunctionLoader
	{
		ExternalFunction fun;
		CodeGenerator code;
		Ip ip;
		Instruction::iterator i;
		const string &name;
	public:
		ExternalFunctionLoader(const string &name);
		~ExternalFunctionLoader();
		ExternalFunction get(){ return fun; }
	private:
		void start();

		TOKEN_CLASS loadSymbol();
		void loadOutput();
		void checkIfInputArgs();
		void loadInput();
		void loadName();
		void loadBody();
		void checkFunctionDeclEnd();

		void throwEof();
		void throwEofInstruction();
		void throwSize(int i = 1);

		void next()
		{
			code.inc();
			throwEof();
			ip = code.get();
		}
	};
}

