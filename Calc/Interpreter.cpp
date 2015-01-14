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

		try{
			exec.setInput(command);
			CodeExecutor::off_stop_computing();
			exec.start();
			
		}
		catch (const CalcException &ex)
		{
			SignalEmitter::get()->call(ex);
		}
		catch (const string &ex)
		{
			SignalEmitter::get()->call(CalcException(ex));
		}
		SignalEmitter::get()->call_execution_complate();
		sendUpdatedVariablesInformations();
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

	VariableInfo Interpreter::getVariableInfo(const char *name)
	{
		try{
			return VariableInfo(name, main_vars.get(name));
		}
		catch (const CalcException &ex)
		{
			return VariableInfo(name, nullptr);
		}
	}

	void Interpreter::sendUpdatedVariablesInformations()
	{
		vector<VariableInfo> updated;
		vector<VariableInfo> added;
		main_vars.getUpdated(added, updated);
		SignalEmitter::get()->call_sig_removed_variables(main_vars.getRemoved());
		if (updated.size())
			SignalEmitter::get()->call_sig_updated_variables(&updated[0], updated.size());
		if (added.size())
			SignalEmitter::get()->call_sig_added_variables(&added[0], added.size());
		
		main_vars.clearRemoved();
	}



	
}