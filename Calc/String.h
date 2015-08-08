#pragma once
#include "Data.h"
#include "Token.h"

namespace PR
{
	//! Klasa reprezentujaca lanuch tekstowy
	class String : public Token
	{
		string data;
	public:
		//! Konstruktor klasy ustawiajacy wartosc.
		//! \param str tekst lancucha tekstowego.
		String(const string &str);

		//! "Move" konstruktor
		//! \param str r-referencja na tekst lanucha tekstowego.
		String(string &&str);
		~String();

		//! Pobranie referencji do zawartosci lanucha.
		virtual const string & getLexemeR() const override;

		//! Pobranie lancucha tekstowego.
		virtual string getLexeme() const override;

		//! Pobiera lanuch tekstowy.
		virtual string toString() const override;

		//! Pobiera lancuch tekstowy.
		virtual string toStringCommpact() const override;

		//! Pobiera lanuch tekstowy.
		virtual string toHtml() const override;

		//! Pobiera zawartosc
		virtual string getValueInfoString() const override;

		//! Zwraca wskaznik na nowa kopie obiektu.
		//! String dziedziczy posrednio z klasy Data.
		virtual shared_ptr<Data> copy() const override;

		//! Laczy dwa lanuchy tekstowe.
		// \param b wskaznik na drugi lancuch tekstowy
		virtual shared_ptr<Data> operator + (shared_ptr<Data> &b) const override;
	};
}
