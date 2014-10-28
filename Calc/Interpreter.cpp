#include "stdafx.h"
#include "Interpreter.h"

namespace PR
{
	variables Interpreter::main_vars = {};

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
		exec.setInput(command);
	//	try{
			CodeExecutor::off_stop_computing();
			exec.start();
	/*	}
		catch (CalcException ex)
		{
			SignalEmitter::get()->call(ex);
		}*/
	}

	void Interpreter::workFromFile(const string &fileName)
	{
		CodeExecutor exec(Interpreter::main_vars);
		exec.setInput(FileLoader(fileName));
		exec.start();
	}
}