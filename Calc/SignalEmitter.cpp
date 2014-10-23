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

	auto SignalEmitter::connect_output(const DataPointerSenderSlot &slot)
		-> boost::signals2::connection
	{
		return sig_data_pointer.connect(slot);
	}

	auto SignalEmitter::connect_errors(const ExceptionSenderSlot &slot)
		-> boost::signals2::connection
	{
		return sig_exception.connect(slot);
	}

	void SignalEmitter::call(const CalcException &exception)
	{
		sig_exception(exception.getMessageR().c_str(), exception.getPosition());
	}

	void SignalEmitter::call(const string &name, const shared_ptr<Data> &data)
	{
		sig_data_pointer(name.c_str(), data.get());
	}
}
