#pragma once

#include <memory>
#include <string>

using std::unique_ptr;
using std::string;

#include "Function.h"
#include "SizeFunction.h"

namespace PR
{
	class FunctionFactory
	{
	public:
		static unique_ptr<Function> load_in(const string &name);

	private:
		FunctionFactory();
		~FunctionFactory();

		static FunctionFactory *instance;
		static void loadInstance();

		FunctionFactory & operator = (const FunctionFactory &b) = delete;
		FunctionFactory(const FunctionFactory &b) = delete;
	};
}

