#include "stdafx.h"
#include "Interpreter.h"

namespace PR
{
	Variables Interpreter::main_vars = Variables(true);

	Interpreter::Interpreter()
	{		
	}

	Interpreter::~Interpreter()
	{
	}

	void Interpreter::connectStopComputing()
	{
		SignalEmitter::get()->connect_stop_computing(CodeExecutor::set_stop_computing);
	}

	void Interpreter::work(const string &command)
	{
		CodeExecutor::recursions = 0;
		CodeExecutor exec(Interpreter::main_vars);
		
		main_vars.getAddedRef().clear();
		main_vars.getRemovedRef().clear();
		main_vars.getUpdatedRef().clear();

		try{
			exec.setInput(command);
			CodeExecutor::off_stop_computing();
			exec.start();

			sendNewVariablesInformations();
			sendUpdatedVariablesInformations();
			sendRemovedVariablesInformations();
		}
		catch (const CalcException &ex)
		{
			SignalEmitter::get()->call(ex);
		}
	}

	void Interpreter::updateFile(const char *file)
	{
		FunctionFactory::delete_external(file);
	}

	void Interpreter::workFromFile(const string &fileName)
	{
		CodeExecutor exec(Interpreter::main_vars);
		exec.setInput(FileLoader(fileName));
		exec.start();
	}

	void Interpreter::changeWorkingDirectory(const char *name)
	{
		FileLoader::changeWorkingDirectory(name);
		FunctionFactory::clear_externals();
	}

	void Interpreter::sendNewVariablesInformations()
	{
		vector<VariableInfo> info;
		prepareVariableInformationVector(main_vars.getAddedRef(), info);

		if (info.size())
			SignalEmitter::get()->call_sig_added_variables(&info[0], info.size());
	}

	void Interpreter::sendUpdatedVariablesInformations()
	{
		vector<VariableInfo> updated;
		prepareVariableInformationVector(main_vars.getUpdatedRef(), updated);
		if (updated.size())
			SignalEmitter::get()->call_sig_updated_variables(&updated[0], updated.size());
	}

	void Interpreter::prepareVariableInformationVector(const vector<string> &src, vector<VariableInfo> &dest)
	{
		if (src.size()==0)
			return;

		dest.reserve(src.size());
		for (const string &name : src)
			dest.push_back(VariableInfo(name, main_vars.get(name).get()));
	}

	void Interpreter::sendRemovedVariablesInformations()
	{
		vector<string> &removed = main_vars.getRemovedRef();
		
		if (removed.size() == 0)
			return;

		vector<const char *> removeList;
		removeList.reserve(removed.size());
		for (const string &name : removed)
			removeList.push_back(name.c_str());

		SignalEmitter::get()->call_sig_removed_variables(&removeList[0], removeList.size());
	}
}