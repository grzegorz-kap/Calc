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
#include "LogFunction.h"
#include "Log10Function.h"
#include "Log2Function.h"
#include "SinFun.h"
#include "CosFun.h"
#include "TanFun.h"
#include "LuFunction.h"
#include "DetFunction.h"
#include "InvFunction.h"
#include "PlotFunction.h"

namespace PR
{
	class FunctionFactory
	{
	public:
		static unique_ptr<Function> load_in(const string &name);
		static ExternalFunction& load_external(const string &name);
		static void delete_external(const string &name);
		static void clear_externals();
	private:
		FunctionFactory();
		~FunctionFactory();

		static FunctionFactory *instance;
		static void loadInstance();

		unordered_map<string, function<unique_ptr<Function>(void)>> builded_in;
		unordered_map<string, ExternalFunction> externals;

		bool readExternal(const string &name);

		FunctionFactory & operator = (const FunctionFactory &b) = delete;
		FunctionFactory(const FunctionFactory &b) = delete;
	};
}

