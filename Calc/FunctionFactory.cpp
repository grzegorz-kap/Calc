#include "stdafx.h"
#include "FunctionFactory.h"


namespace PR
{
	FunctionFactory * FunctionFactory::instance = nullptr;

	FunctionFactory::FunctionFactory()
	{
		insert<MpfFunction>("mpf_float");
		insert<LogFunction>("log");
		insert<Log10Function>("log10");
		insert<Log2Function>("log2");
		insert<SinFun>("sin");
		insert<CosFun>("cos");
		insert<TanFun>("tan");
		insert<LuFunction>("lu");
		insert<DetFunction>("det");
		insert<InvFunction>("inv");
		insert<PlotFunction>("plot");
		insert<Plot3Function>("plot3");
		insert<SurfaceFunction>("mesh");
		insert<RandFunction>("rand");
		insert<EyeFunction>("eye");
		insert<OnesFunction>("ones");
		insert<ZerosFunction>("zeros");
		insert<FixFunction>("fix");
		insert<CeilFunction>("ceil");
		insert<ModFunction>("mod");
		insert<RoundFunction>("round");
		insert<CotanFun>("cot");
		insert<ConjFunction>("conj");
		insert<SizeFunction>("size");
		insert<LengthFunction>("length");
		insert<NumelFunction>("numel");
		insert<IsColumnFunction>("iscolumn");
		insert<IsEmptyFunction>("isempty");
		insert<IsRowFunction>("isrow");
		insert<IsScalarFunction>("isscalar");
		insert<IsVectorFunction>("isvector");
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
