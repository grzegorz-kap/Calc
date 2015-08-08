#pragma once

#include <string>
#include <vector>
#include <memory>

using std::vector;
using std::string;
using std::shared_ptr;

#include "Token.h"

namespace KLab
{
	//! Klasa reprezentujaca funkcje zewnetrzna.
	class ExternalFunction
	{
		//! Nazwy parametrow wyjsciowych.
		vector<string> output;

		//! Nazwy argumentow wejsciowych.
		vector<string> input;

		//! Nazwa funkcji.
		string name;

		//! \brief Cialo funkcji.
		//! Zawiera zestaw instrukcji jezyka.
		vector<vector<shared_ptr<Token>>> body;

		//! Okresla czy plik zawierajacy funkcje, zostal zaktualizowany.
		bool updated;

	public:
		ExternalFunction();
		~ExternalFunction();

		void set_updated(); //!< Ustawienie informacji, ze plik z funkcja zostal zaktualizowany.
		void reset_updated(); //!< Zresetowanie informacji o aktualizacji pliku  funkcyjnego.
		bool getUpdated(); //!< Pobranie informacji o aktulizacji pliku z funkcja.

		//! Dodanie parametru wyjsciowego.
		//! \param name nazwa parametru do dodania.
		void addOutput(string &&name);

		//! Dodanie parametru wyjsciowego.
		//! \param name nazwa parametru do dodania.
		void addOutput(const string &name);

		//! Dodanie parametru wejsciowego.
		//! \param name nazwa parametru do dodania.
		void addInput(string &&name);

		//! Dodanie parametru wejsciowego.
		//! \param name nazwa parametru do dodania.
		void addInput(const string &name);

		//! Ustawia nazwe funkcji.
		void setName(string &&nameA);

		//! Ustawia nazwe funkcji.
		void setName(const string &nameA);

		//! Zwraca nazwe funkcji.
		const string & getName() const;

		//! Zwraca liste argumentow wejsciowych.
		const vector<string>& getInput()const;

		//! Zwraca liste argumentow wyjsciowych.
		const vector<string>& getOutput() const;

		//! Zwraca cialo funkcji.
		const vector<vector<shared_ptr<Token>>> & getCode() const;

		//! Dodanie instrukcji do ciala funkcji.
		void addInstruction(vector<shared_ptr<Token>> &&in);
	};
}
