#pragma once

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;

#include "CalcException.h"
#include "Matrix.h"
#include "Output.h"


namespace PR
{
	class Function
	{
	protected:
		string name;
		int max_args_count;
		int min_args_count;
		vector<shared_ptr<Data>> arguments;
	public:
		Function();
		~Function();

		virtual shared_ptr<Data> run();

		string getName() const { return name; }

		virtual void set(const vector<shared_ptr<Data>> &args);

	protected:

		void checkArgsCount(int i);
	};
}