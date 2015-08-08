#pragma once

#include <memory>
#include <string>

using std::unique_ptr;
using std::make_unique;
using std::string;

#include "i_order_map.h"
#include "Token.h"
#include "ArithmeticOperators.h"
#include "RelationalOperators.h"
#include "LogicalOperators.h"
#include "AssignmentOperator.h"
#include "TranspositionOperator.h"
#include "Colon2Operator.h"
#include "Colon3Operator.h"

namespace PR
{
	//! Fabryka operatorow.
	class OperatorsFactory
	{
	public:
		OperatorsFactory & operator = (const OperatorsFactory &) = delete;
		OperatorsFactory(const OperatorsFactory &) = delete;
		~OperatorsFactory();

		//! \brief  Wyodrabnia operator z tekstu wejsciowego.
		//! \param name tekst wejsciowy.
		//! \param startIdx indeks elementu w tekscie od ktorego rozpoczac wyszukiwanie.
		//! \param length referencja na dlugosc identyfikatora znalezionego operatora.
		static unique_ptr<Operator> get(const string &name, int startIdx, int &length);

		//! \brief Zwraca operator o wskazanej nazwie.
		//! \param name symbol operatora do pobrania.
		static unique_ptr<Operator> simple_get(const string &name);
	private:
		OperatorsFactory();
		static OperatorsFactory * instance; //<! Instancja fabryki
		i_order_map<string, unique_ptr<Operator>(*)()>  operators; //<! Mapa operatorow

	private:
		static void init();
	};
}
