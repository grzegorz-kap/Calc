#include "stdafx.h"
#include "SignalEmitter.h"


namespace PR
{
	SignalEmitter* SignalEmitter::instance = nullptr;

	SignalEmitter::SignalEmitter()
	{
		sig_data_value			= new DataValueSender();
		sig_exception			= new ExceptionSender();
		sig_stop_computing		= new StopComputingSender();
		sig_added_variables		= new AddedVariablesSender();
		sig_updated_variables	= new AddedVariablesSender();
		sig_removed_variables	= new CharStringSender();
	}

	SignalEmitter::~SignalEmitter()
	{
		delete	sig_data_value		   ;
		delete	sig_exception		   ;
		delete	sig_stop_computing	   ;
		delete	sig_added_variables	   ;
		delete	sig_updated_variables  ;
		delete	sig_removed_variables  ;
	}

	SignalEmitter* SignalEmitter::get()
	{
		if (instance == nullptr)
			instance = new SignalEmitter();
		return instance;
	}

	void SignalEmitter::connect_output(const DataPointerSenderSlot &slot)
	{
		sig_data_value->connect(slot);
	}

	void SignalEmitter::connect_errors(const ExceptionSenderSlot &slot)
	{
		sig_exception->connect(slot);
	}

	void SignalEmitter::connect_stop_computing(const StopComputingSlot &slot)
	{
		sig_stop_computing->connect(slot);
	}

	void SignalEmitter::connect_added_variables_slot(const AddedVariablesSlot &slot)
	{
		sig_added_variables->connect(slot);
	}

	void SignalEmitter::connect_updated_variables_slot(const AddedVariablesSlot &slot)
	{
		sig_updated_variables->connect(slot);
	}

	void SignalEmitter::connect_removed_variables_slot(const CharStringSenderSlot &slot)
	{
		sig_removed_variables->connect(slot);
	}

	void SignalEmitter::call(const CalcException &exception)
	{
		(*sig_exception)(exception.getMessageR().c_str(), exception.getPosition());
	}

	void SignalEmitter::call(const string &name, const shared_ptr<Data> &data)
	{
		(*sig_data_value)(name.c_str(), data.get());
	}

	void SignalEmitter::call_stop()
	{
		(*sig_stop_computing)();
	}

	void SignalEmitter::call_sig_added_variables(const VariableInfo *data, int num)
	{
		(*sig_added_variables)(data, num);
	}

	void SignalEmitter::call_sig_updated_variables(const VariableInfo *data, int num)
	{
		(*sig_updated_variables)(data, num);
	}

	void SignalEmitter::call_sig_removed_variables(const char **data, int num)
	{
		(*sig_removed_variables)(data, num);
	}
}
