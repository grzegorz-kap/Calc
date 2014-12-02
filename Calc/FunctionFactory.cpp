#include "stdafx.h"
#include "FunctionFactory.h"


namespace PR
{
	FunctionFactory * FunctionFactory::instance = nullptr;

	FunctionFactory::FunctionFactory()
	{
		builded_in.insert({ "size", [](){return make_unique<SizeFunction>(); } });
		builded_in.insert({ "mpf_float", [](){return make_unique<MpfFunction>(); } });
		builded_in.insert({ "log", [](){return make_unique<LogFunction>(); } });
		builded_in.insert({ "log10", [](){return make_unique<Log10Function>(); } });
		builded_in.insert({ "log2", [](){return make_unique<Log2Function>(); } });
		builded_in.insert({ "sin", [](){return make_unique<SinFun>(); } });
		builded_in.insert({ "cos", [](){ return make_unique<CosFun>(); } });
		builded_in.insert({ "tan", [](){return make_unique<TanFun>(); } });
		builded_in.insert({ "lu", [](){return make_unique<LuFunction>(); } });
		builded_in.insert({ "det", [](){return make_unique<DetFunction>(); } });
		builded_in.insert({ "inv", [](){return make_unique<InvFunction>(); } });
		builded_in.insert({ "plot", [](){return make_unique <PlotFunction>(); } });
		builded_in.insert({ "plot3", [](){return make_unique<Plot3Function>(); } });
		builded_in.insert({ "surface", [](){return make_unique<SurfaceFunction>(); } });
		builded_in.insert({ "rand", [](){return make_unique<RandFunction>(); } });
		builded_in.insert({ "fix", [](){return make_unique<FixFunction>(); } });
		builded_in.insert({ "floor", [](){return make_unique<FloorFunction>(); } });
		builded_in.insert({ "ceil", [](){return make_unique<CeilFunction>(); } });
		builded_in.insert({ "mod", [](){return make_unique<ModFunction>(); } });
		builded_in.insert({ "round", [](){return make_unique<RoundFunction>(); } });
		builded_in.insert({ "cot", [](){return make_unique<CotanFun>(); } });
	}

	FunctionFactory::~FunctionFactory()
	{
	}

	unique_ptr<Function> FunctionFactory::load_in(const string &name)
	{
		loadInstance();
		auto result = instance->builded_in.find(name);
		if (result == instance->builded_in.end())
			return nullptr;
		else
			return result->second();
	}

	ExternalFunction& FunctionFactory::load_external(const string &name)
	{
		loadInstance();
		instance->readExternal(name);
		return instance->externals[name];
	}

	void FunctionFactory::delete_external(const string &file)
	{
		loadInstance();
		instance->externals.erase(file);
	}

	void FunctionFactory::clear_externals()
	{
		loadInstance();
		instance->externals.clear();
	}

	bool FunctionFactory::readExternal(const string &name)
	{
			ExternalFunctionLoader fun(name);
			instance->externals[name] = fun.get();
			return false;
	}

	void FunctionFactory::loadInstance()
	{
		if (instance == nullptr)
			instance = new FunctionFactory();
	}
}
