#include "stdafx.h"
#include "ExternalFunction.h"

namespace PR
{
	ExternalFunction::ExternalFunction()
	{
	}

	ExternalFunction::~ExternalFunction()
	{
	}

	void ExternalFunction::set_updated()
	{
		updated = true;
	}

	void ExternalFunction::reset_updated()
	{
		updated = false;
	}

	bool ExternalFunction::getUpdated()
	{
		return updated;
	}

	void ExternalFunction::addOutput(string &&name)
	{
		output.push_back(std::move(name));
	}

	void ExternalFunction::addOutput(const string &name)
	{
		output.push_back(name);
	}

	void ExternalFunction::addInput(string &&name)
	{
		input.push_back(std::move(name));
	}

	void ExternalFunction::addInput(const string &name)
	{
		input.push_back(name);
	}

	void ExternalFunction::setName(string &&nameA)
	{
		name = std::move(nameA);
	}

	void ExternalFunction::setName(const string &nameA)
	{
		name = nameA;
	}

	const string & ExternalFunction::getName() const
	{
		return name;
	}

	const vector<string>& ExternalFunction::getInput()const
	{
		return input;
	}

	const vector<string>& ExternalFunction::getOutput() const
	{
		return output;
	}

	const vector<vector<shared_ptr<Token>>> & ExternalFunction::getCode()const
	{
		return body;
	}

	void ExternalFunction::addInstruction(vector<shared_ptr<Token>> &&in)
	{
		body.push_back(std::move(in));
	}
}