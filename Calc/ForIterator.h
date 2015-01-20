#pragma once

#include <vector>

using std::vector;

#include "Data.h"
#include "Variables.h"
#include "TypePromotor.h"

namespace PR
{
	//! Iterator petli for
	class ForIterator
	{
		shared_ptr<Data> data; //!< Zestaw iterowanych wartosci.
		int size;			   //!< Rozmiar zestawu iterowanych wartosci.
		int idx;			//<! Indeks aktualnej iteracji.
		Variables &vars;    //<! Referencja na przestrzen robocza zmiennych.
		string iterator_name; //!< Nazwa iteratora.
		int code_begin; //!< Adres poczatku ciala petli.
		int code_end; //!< Adres konca petli.
	public:
		//! \param ref referencja na przestrzen robocza zmiennych.
		ForIterator(Variables &ref);
		~ForIterator();

		//! Ustawia nazwe iteratora.
		void setName(const string &name){ iterator_name = name; }

		//! Ustawia zestaw iterowanych wartosc.
		//! \param data_vector musi zawierac pojedyncza wartosc numeryczna.
		void setData(vector<shared_ptr<Data>> &&data_vector);

		//! Ustawia adres poczatku ciala patli.
		void setCodeBegin(int begin){ code_begin = begin; }

		//! Ustawia adres konca petli.
		void setCodeEnd(int end){ code_end = end; }

		//! Zwraca adres poczatku petli.
		int getCodeBegin() const { return code_begin; }

		//! Zwraca adres konca petli.
		int getCodeEnd() const { return code_end; }

		//! Sprawdza czy przeiterowano caly zestaw wartosci.
		bool end() const { return idx >= size; }

		//! Laduje nastepna wartosc z zestawu do iteratora petli.
		void loadNext();
	};

}
