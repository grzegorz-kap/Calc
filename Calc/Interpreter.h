  #pragma once
#include "export.h"
#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <memory>

using std::string;
using std::cout;

#include "CodeExecutor.h"

namespace PR
{
	//! \brief Glowna klasa interpretera.
	class CALC_API Interpreter
	{
		static Variables main_vars; //!< Przechowuje glowna przestrzen robocza.
	public:
		//! Domyslny konstruktor
		Interpreter(); 
		~Interpreter();

		//! \brief Wykonuje instrukcje jezyka.
		//! \param command tekst z instrukcjami jezyka do wykonania.
		void work(const string &command);

		//! \brief Ustawia mozliwosc przerwania obliczen.
		void connectStopComputing();

		//! \brief Powoduje panowne sparsowanie instrukcji z pliku.
		//! \param name nazwa pliku do odswiezenia.
		void updateFile(const char *name);

		//! \brief Zmienia aktualny katalog roboczy
		//! \param dir sciezka do nowego katalogu roboczego
		void changeWorkingDirectory(const char *dir);
		
		//! \brief Udostepnia informacje o zmiennej.
		//! Udostepnie informacje o zmiennej, potrzebne do wyswietlenia w interfejsie graficznym.
		//! \param name nazwa zmiennej.
		//! \return Informacje o zmiennej.
		VariableInfo getVariableInfo(const char *name);

	private:
		//! Wysyla informacje o zaaktualizowanych zmiennych do GUI.
		void sendUpdatedVariablesInformations();
	};
}

