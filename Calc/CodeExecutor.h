#ifndef CODE_EXECUTOR_H
#define CODE_EXECUTOR_H

#pragma once

#include <memory>
#include <vector>
#include <map>

using std::map;
using std::unique_ptr;
using std::vector;

#include "CodeGenerator.h"
#include "FunctionFactory.h"
#include "ExternalFunction.h"
#include "MatrixBuilderFactory.h"
#include "SignalEmitter.h"
#include "TypePromotor.h"
#include "Variables.h"
#include "ForIterator.h"

namespace KLab
{
	//! Klasa obslugujaca wykonywanie kodu przez interpreter.
	class CodeExecutor
	{
	public:
		//! Aktualna liczba zagniezdzonych wywolan funkcji zewnetrznych.
		static int recursions;

		//! Limit zagniezdzonych wywolan funkcji zewnetrznych
		static int recursion_limit;

		//! \brief Konstruktor domyslny.
		/*! Tworzy lokalna przestrzen robocza zmiennych. */
		CodeExecutor();

		//! \brief Konstruktor z ustawieniem referencji na przestrzen robocza zmiennych.
		/*! Operacje beda wykonywane na ustawionej przestrzeni roboczej zmiennych.
		*	@param ref referencja na obiekt zawierajacy przestrzen robocza zmiennych.
		*/
		CodeExecutor(Variables &ref);
		~CodeExecutor();

		//! \brief Ustawienie danych wejsciowych
		//! \param in Tekst zawierajacy instrukcje jezyka do wykonania.
		void setInput(const string &in);

		//! \brief Ustawienie danych wejsciowych
		//! \param in plik zawierajacy instrukcje do przetworzenia
		void setInput(FileLoader &in);

		//! Rozpoczyna wykonywanie kodu
		void start();

		//! Powoduje przerwanie obliczen
		static void set_stop_computing();

		//! Resetuje flage przerwania obliczen
		static void off_stop_computing();

		//! Oblicza wartosc pojedynczego wyrazenia
		//! \param onp tablica zawierajaca wyrazenie postfiksowe
		//! \param onp referencja na przestrzen robocza
		static vector<shared_ptr<Data>> run_single(const vector<shared_ptr<Token>> &onp, Variables &vars);

		//! Metoda sprawdzajaca czy token sluzy do indeksowania macierzy
		//! Ustala czy token to ":" lub "end" uzywane do indeksowania macierzy.
		//! \param t symbol leksykalny do sprawdzenia
		static bool isMatrixEndOrColon(const shared_ptr<Token> &t);
	private:

		static bool stop_computing;			//!< Flaga wskazuja czy nalezy przerwac obliczenia.
		bool eval_flag;						//!< Flaga okreslajaca typ wykonywania.
		vector<shared_ptr<Data>> stack;		//!< Stos uzywany w trakcie obliczania wartosci wyrazenia.
		Instruction::const_iterator i;		//!< Iterator na elementy instrukcji.
		vector<int> conditions;				//!< Adresy wyrazen warunkowych peti while.
		vector<ForIterator> for_iterators;	//!< Stos iteratorow dla petli for.
		Ip ip;								//!< Iterator na aktualnie wykonywana instrukcje.
		CodeGenerator code;					//!< Obiekt zawierajacy wczytany kod.
		bool output_off_flag;				//!< Flaga okreslajaca czy wyswietlic wynik wyrazenia.
		bool assignment_flag;				//!< Flaga okreslajaca czy wystapilo przypisanie.
		bool _single_run;					//!< Flaga okreslajaca tryb wykonywania.
		bool _single_id_flag;			    //!< Flaga okreslajaca typ obliczanego wyrazenia.
		AssignmentsData assignment;			//!< Zawiera informacje o zmiennych do wyswietlenia.
		Variables internal_vars;			//!< Lokalna przestrzen robocza. Nie u¿ywana bezpoœrednio.
		Variables &vars_ref;				//!< Referencja na przestrzen robocza zmiennych.
		string _file;						//!< File name in casue of script or external function computation.

		//! Constructor for external function execution.
		CodeExecutor(const ExternalFunction &fun, const vector<shared_ptr<Data>> &args);

		//! Find specific element in data stack.
		vector<shared_ptr<Data>>::iterator find(TOKEN_CLASS _class, bool ex = false);

		//! Execute single instruction.
		shared_ptr<Data> run(bool multi = true);

		//! \brief Rozpoczecie wykonywania kodu.
		//! \param in tekst z intstrukcja do wykonania.
		void start(const string &in);
		void onOperator();
		void onShortCircuitJumper();
		void onMatrixEnd();
		void onFunction();
		void onFunctionArgs();
		void onVariableFunction(vector<shared_ptr<Data>> &args, shared_ptr<Data> &var);
		void onExternalFunction(const vector<shared_ptr<Data>> &args, const string &name);
		void onAssignment();
		void defaultAssignment();
		void onIF();
		void onEval(vector<shared_ptr<Data>> &args);
		void onElseIf();
		bool checkIF();
		void onWHILE();
		void onWhileEnd();
		bool checkWhile();
		bool checkFor();
		void onForKeyword();
		void onForEndKeyword();
		void onBreakKeyword();
		void onContinueKeyword();
		bool checkLoopsControl();
		void onMatrixAllOrLastInex();
		void onVariablesManagement();
		void loadFromFile(vector<shared_ptr<Data>> &args);
		void onID();
		bool onScript();
		shared_ptr<Data> pop();
		void pushToken(TOKEN_CLASS t);
		bool isKeyword(TOKEN_CLASS _class);
		void setIPTo(const vector<TOKEN_CLASS> &set, int balance);
		void next();
		void prev();
		void throwError(const string &name, string src = "");
		static const vector<TOKEN_CLASS> IF_FIND;
		static const vector<TOKEN_CLASS> ELSE_FIND;
		static const vector<TOKEN_CLASS> WHILE_FIND;
		static const vector<TOKEN_CLASS> FOR_FIND;
		static const vector<TOKEN_CLASS> ELSEIF_FIND;
		static const vector<TOKEN_CLASS> BRK_CONT_FIND;
	};
}

#endif
