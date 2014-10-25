#include "stdafx.h"
#include "Interpreter.h"

namespace PR
{
	variables Interpreter::main_vars = {};

	Interpreter::Interpreter()
	{		
		if (Data::TYPE_MAP_BUILDED == false)
		{
			Data::TYPE_MAP_BUILDED = true;
			Data::TYPE_MAP[typeid(Matrix<double>)] = TYPE::M_DOUBLE;
			Data::TYPE_MAP[typeid(ComplexNumber<double>)] = TYPE::DOUBLE;
		}
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
		CodeExecutor exec(Interpreter::main_vars);
		exec.setInput(command);
		try{
			CodeExecutor::off_stop_computing();
			exec.start();
		}
		catch (CalcException ex)
		{
			SignalEmitter::get()->call(ex);
		}
	}

	void Interpreter::workFromFile(const string &fileName)
	{
		CodeExecutor exec(Interpreter::main_vars);
		exec.setInput(FileLoader(fileName));
		exec.start();
	}
}