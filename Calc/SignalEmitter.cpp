#include "stdafx.h"
#include "SignalEmitter.h"


namespace PR
{
	SignalEmitter* SignalEmitter::instance = nullptr;

	SignalEmitter::SignalEmitter()
	{
	}

	SignalEmitter::~SignalEmitter()
	{
	}

	SignalEmitter* SignalEmitter::get()
	{
		if (instance == nullptr)
			instance = new SignalEmitter();
		return instance;
	}

	void SignalEmitter::connect_output(const DataPointerSenderSlot &slot)
	{
		sig_data_pointer.connect(slot);
	}

	void SignalEmitter::connect_errors(const ExceptionSenderSlot &slot)
	{
		sig_exception.connect(slot);
	}

	void SignalEmitter::connect_stop_computing(const StopComputingSlot &slot)
	{
		sig_stop_computing.connect(slot);
	}

	void SignalEmitter::call(const CalcException &exception)
	{
		sig_exception(exception.getMessageR().c_str(), exception.getPosition());
	}

	void SignalEmitter::call(const string &name, const shared_ptr<Data> &data)
	{
		sig_data_pointer(name.c_str(), data.get());
	}

	void SignalEmitter::call_stop()
	{
		sig_stop_computing();
	}
}
