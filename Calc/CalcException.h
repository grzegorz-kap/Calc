#pragma once

#include <exception>
#include <string>

using std::exception;
using std::string;

namespace PR
{
	//! Klasa przechowujaca informacje o bledzie.
	class CalcException : public exception
	{
		string message; //!< Komunikat bledu.
		string command; //!< Dodatkowe informacje.
		int position;   //!< Kolumna w ktorej wystapil blad.
		int line;		//!< Wiersz w ktorym wystapil blad.
	public:

		//! Konstruktor nowego obiektu
		// \param message komunikat bledu.
		// \param command dodatkowe informacje.
		// \param position numer kolumny w ktorym wystapil blad
		// \param line numer wiersza w ktorym wystapil blad
		CalcException(const string &message, const string &command = "", int position = 1, int line = 0);

		//! Konstruktor nowego obiektu
		// \param messageA tresc komunikatu.
		// \param positionA numer kolumny wystapienia bledu
		CalcException(const string &messageA, int positionA);
		~CalcException();

		string getMessage()const{ return message; } //!< Zwraca komunikat bledu
		const string& getMessageR()const{ return message; } //!< Zwraca komunikat bledu.
		string getCommand()const{ return command; } //!< Zwraca dodatkowe informacje.
		int getPosition()const{ return position; } //!< Zwraca numer wiersza.
		int getLine()const{ return line; }	//!< Zwraca numer kolummy.
	};

}
