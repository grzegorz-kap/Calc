#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

using std::unique_ptr;
using std::string;
using std::unordered_map;
using std::function;

#include "FileLoader.h"
#include "Function.h"
#include "ExternalFunction.h"
#include "ExternalFunctionLoader.h"
#include "LexicalAnalyzer.h"

#include "SizeFunction.h"
#include "MpfFunction.h"
#include "ElementaryMathFunctions.h"
#include "TrigonometryFunctions.h"
#include "LinearAlgebraFunctions.h"
#include "PlotingFunctions.h"
#include "MatrixGenerationFunctions.h"
#include "ModFunction.h"
#include "RoundingFunctions.h"

namespace PR
{
	//! Fabryka funkcji.
	class FunctionFactory
	{
	public:
		//! \brief Zwraca implementacje interfejsu funkcji wbudowanej.
		//! \param name nazwa funkcji wbudowanej.
		static unique_ptr<Function> load_in(const string &name);

		//! \brief Pobranie funkcji zewnterznej.
		//! \param name nazwa funkcji zewnetrznej.
		//! \return Referencja na obiekt funkcji zewnetrznej.
		static ExternalFunction& load_external(const string &name);

		//! \brief Usuwa funkcje zewnetrzna z pamieci podrecznej.
		//! \param name nazwa funkcji do usuniecia.
		static void delete_external(const string &name);

		//! Czysci pamiec podreczna funkcji zewnetrznych
		static void clear_externals();
	private:
		FunctionFactory();
		~FunctionFactory();

		//! \brief Wskaznik na obiekt klasy.
		static FunctionFactory *instance;

		//! \brief Pobranie wskaznika na obiekt klasy.
		/*!
			Ewentualnie alokauje nowey obiekt klasy w pamieci.
		*/
		static void loadInstance();

		unordered_map<string, function<unique_ptr<Function>(void)>> builded_in; //!< Mapa funkcji wbudowanych.
		unordered_map<string, ExternalFunction> externals; //!< Mapa zewnetrznych funkcji w pamieci podrecznej.

		//! \brief Pobranie funkcji zewnetrznej z pliku.
		//! \param name nazwa funkcji.
		bool readExternal(const string &name); 

		FunctionFactory & operator = (const FunctionFactory &b) = delete;
		FunctionFactory(const FunctionFactory &b) = delete;

		//! \brief Wstawa nowa funkcje wbudowana do mapy funkcji wbudowanych.
		//! \param T typ funkcji wbudowanej.
		//! \param name nazwa funkcji
		template <class T>
		void insert(const string &name)
		{
			builded_in.insert({ name, [](){return make_unique<T>(); } });
		}
	};
}

