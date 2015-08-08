#pragma once

#include "Token.h"
#include "Variables.h"

#include <vector>
#include <memory>
#include <map>
#include <string>

using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

namespace KLab
{
	//! Rodzaje operacji przypisania.
	enum ASSIGNMENT_TYPE : char
	{
		SINGLE, //!< Przypisanie pojedynczej wartosci.
		MULTI,  //!< Przypisanie wielu wartosci jednoczesnie.
		SUBSCRIPTED //!< Modyfikacja komorek macierzy.
	};

	typedef vector<shared_ptr<Token>>::iterator instr_iter;
	typedef vector<shared_ptr<Data>>::iterator stack_iterator;

	class IAssignment : public Token
	{
	public:
		const ASSIGNMENT_TYPE _assignment_type; //<! Rodzaj operacji przypisania.

		//<! Konstruktor ustawiajacy rodzaj przypisania.
		//! \param _type rodzaj operacji przypisania.
		IAssignment(const ASSIGNMENT_TYPE &_type);
		~IAssignment();

		//! Wczytuje cel przypisania z instrukcji.
		//! \param start iterator na poczatek instrukcji.
		//! \param end iterator na koniec instrukcji.
		virtual void loadTarget(instr_iter &start, instr_iter &end);

		//! Dokonuje operacji przypisania.
		//! \param vars referencja na przestrzen robocza zmiennych.
		//! \param first iterator na poczatek stosu danych.
		//! \param last iterator na koniec stosu danych.
		//! \param assignment referencja na miejsce zapisu informacji o wykonanych przypisaniach.
		virtual void doAssignment(Variables &vars, stack_iterator &first, stack_iterator &last, AssignmentsData &assignment);

		//! Zwraca liczbe elementow, bedacych celem przypisania.
		virtual int getTargetSize() const;

		//! Dokonuje zapisu do wskazanej przestrzeni roboczej.
		//! \param vars referencja na przestrzen robocza.
		//! \param key nazwa pod ktora zostanie zapisana wartosc.
		//! \param data wartosc do zapisania.
		static variables_map_pair assign(Variables &vars, const string &key, const shared_ptr<Data> &data);
	};
}
