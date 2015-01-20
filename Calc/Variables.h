#ifndef VARIABLES_H
#define VARIABLES_H
#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include "Data.h"
#include "VariableInfo.h"
using std::string;
using std::map;
using std::vector;
using std::shared_ptr;
namespace PR
{
	typedef map<string, shared_ptr<Data>> variables_map;
	typedef variables_map::iterator variables_map_iter;
	typedef std::pair<variables_map_iter, bool> variables_map_pair;
	typedef vector<variables_map_pair> AssignmentsData;

	//! Klasa reprezentuje przestrzen robocza.
	class Variables
	{
		variables_map mem;
		bool main;
		vector<string> removed;
	public:
		//! \param main okresla, czy bedzie to glowna przestrzen robocza zmiennych.
		Variables(bool main = false);
		~Variables();

		//! Pobranie wartosci zmiennej.
		//! \param name nazwa zmiennej do pobrania.
		//! \param ex wyjatek, gdy nie znaleziono zmiennej.
		shared_ptr<Data> get(const string &name, bool ex = true);
		
		//! Usuwa wszystkie zmienne z pamieci.
		void clear();

		//! Usuwa zmienna z pamieci
		//! \param name nazwa zmiennej do usuniecia.
		void clear(const string &name);

		//! Pobranie iteratora na wartosc zmiennej.
		//! \param name nazwa pobieranej zmiennej.
		//! \param ex okresla czy rzucic wyjatek, gdy zmienna nie istnieje.
		variables_map_iter getIterator(const string &name, bool ex = true);

		//! Dokonuje zapisu nowej wartosci do pamieci.
		//! \param name nazwa zmiennej.
		//! \param data wartosc ktora nalezy zapisac.
		variables_map_pair set(const string &name, const shared_ptr<Data> &data);	

		//! Czyszczenie lub zapis do pliku zmiennych.
		//! \param operation typ operacji (clear lub save).
		//! \param working_dir folder wyjsciowych w przypadku zapisu do pliku.
		//! \param args zestaw argumentow dla operacji.
		void menage(const string &operation, const string &working_dir, vector<shared_ptr<Data>> &args);

		//! Zwraca liste zaktualizowanych i dodanych zmiennych.
		//! \param added referencja na liste dodanych zmiennych.
		//! \param updated referencja na liste zmodyfikowanych zmiennych.
		void getUpdated(vector<VariableInfo> &added, vector<VariableInfo> &updated) const;

		//! Pobiera liste nazw usunietych zmiennych.
		vector<string> getRemoved();

		//! Czysci liste nazw usunietych zmiennych.
		void clearRemoved();
	private:
		void remove(vector<shared_ptr<Data>> &args);
		void safe_to_file(const string &working_dir, vector<shared_ptr<Data>> &args);
		void safe_to_file(std::ofstream &file, vector<shared_ptr<Data>> &args);
	};
}
#endif