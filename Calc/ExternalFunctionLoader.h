#pragma once

#include "ExternalFunction.h"
#include "CodeGenerator.h"

namespace PR
{
	//! Laduje funkcje z pliku.
	class ExternalFunctionLoader
	{
	private:
		ExternalFunction fun;
		CodeGenerator code;
		Ip ip;
		Instruction::iterator i;
		const string &name;

	public:

		//! Konstruktor klasy.
		//! \param name nazwa funkcji do wczytania
		ExternalFunctionLoader(const string &name);
		~ExternalFunctionLoader();

		//! Zwraca obiekt wczytanej funkcji.
		ExternalFunction get();

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
		void next(); /* Load next from code generator */
	};
}

