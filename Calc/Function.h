#pragma once

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;

#include "CalcException.h"
#include "TypePromotor.h"

namespace KLab
{
	//! Klasa stanowiaca interfejs dla funkcji wbudowanych.
	class Function
	{
	protected:
		string name; //!< Nazwa funkcji
		int max_args_count; //!< Minimalna liczba agumentow.
		int min_args_count; //!< Maksymalna liczba argumentow.
		int output; //!< Liczba oczekiwanych parametrow wejsciowych.
		vector<shared_ptr<Data>> arguments; //!< Tablica argumentow funkcji.
	public:
		//! Domyslny konstruktor.
		Function();
		~Function();

		//! Pobranie nazwy funkcji.
		virtual string getName() const { return name; }

		//! Wykonanie funkcji.
		virtual shared_ptr<Data> run();

		//! Ustawienie argumentow funkcji.
		//! \param args lista argumentow wejsciowych.
		//! \param output liczba oczekiwanych parametrow wyjsciowych.
		virtual void set(const vector<shared_ptr<Data>> &args, int output = 1);

	protected:
		//! sprawdzenie czy liczba argumentow jest poprawna.
		//! \param i liczba przekazanych argumentow wejsciowych.
		void checkArgsCount(int i);
	};
}