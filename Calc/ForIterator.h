#pragma once

#include <vector>

using std::vector;

#include "Data.h"
#include "Variables.h"
#include "TypePromotor.h"

namespace PR
{
	class ForIterator
	{
		shared_ptr<Data> data;
		int size;
		int idx;
		Variables &vars;
		string iterator_name;
		int code_begin;
		int code_end;
	public:
		ForIterator(Variables &ref);
		~ForIterator();

		void setName(const string &name){ iterator_name = name; }
		void setData(vector<shared_ptr<Data>> &&data_vector);
		void setCodeBegin(int begin){ code_begin = begin; }
		void setCodeEnd(int end){ code_end = end; }

		int getCodeBegin() const { return code_begin; }
		int getCodeEnd() const { return code_end; }

		bool eof() const { return idx >= size; }
		void loadNext();
	};

}
