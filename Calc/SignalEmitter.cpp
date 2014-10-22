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

	auto SignalEmitter::connect(const DataPointerSenderSlot &slot)
		-> boost::signals2::connection
	{
		return sig.connect(slot);
	}

	void SignalEmitter::call(const string &name, const shared_ptr<Data> &data)
	{
		sig(name.c_str(), data.get());
	}
}
