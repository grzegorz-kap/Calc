#include "stdafx.h"
#include "FunctionFactory.h"


namespace PR
{
	FunctionFactory * FunctionFactory::instance = nullptr;

	FunctionFactory::FunctionFactory()
	{
		builded_in.insert({ "size", [](){return make_unique<SizeFunction>(); } });
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
	
		
			instance->readExternal(name);
		return instance->externals[name];
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
