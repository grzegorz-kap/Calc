#pragma once
#include "Data.h"

#include <vector>
#include <memory>
#include <algorithm>

using std::vector;
using std::shared_ptr;

namespace PR
{
	//! Zawiera zestaw wartosci zwroconych przez funkcje.
	class Output : public Data
	{
		vector<shared_ptr<Data>> out;
	public:
		//! Okresla czy zwrocone wartosci pochodza z funkcji zewnetrznej.
		bool _extern;

		Output();
		~Output();

		//! Zwraca liczbe argumentow wejsciowych.
		int getArgumentsNumber() const { return out.size(); }

		//! Dodaje wartosc do zestawu.
		void add(const shared_ptr<Data> &item);
		vector<shared_ptr<Data>>& getOutput();
		virtual bool isOutput() const override;
		virtual Output * cast_output() override;

		//! Okresla typ o najwyjzszym priotytecie z zestawu watosci.
		virtual TYPE max_type() const override;

		//! Okresa czy zwrocone wartosci sa numeryczne.
		virtual bool isNumeric() const override;
	};
}
