#pragma once

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;

#include "CalcException.h"
#include "TypePromotor.h"


namespace PR
{
	class Function
	{
	
	protected:
		string name;
		int max_args_count;
		int min_args_count;
		int output;
		vector<shared_ptr<Data>> arguments;
	public:
		Function();
		~Function();

		string getName() const { return name; }
		virtual shared_ptr<Data> run();
		virtual void set(const vector<shared_ptr<Data>> &args,int output=1);

	protected:

		void checkArgsCount(int i);
	};
}