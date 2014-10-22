#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include <boost\signals2\signal.hpp>
#include <boost\bind\bind.hpp>

#include <string>
#include <memory>

#include "Data.h"

namespace PR
{
	class CodeExecutor;
	class CALC_API SignalEmitter
	{
		typedef boost::signals2::signal < void(const char *, const Data *) > DataPointerSender;
		typedef DataPointerSender::slot_type DataPointerSenderSlot;
	private:
		DataPointerSender sig;
		static SignalEmitter * instance;
		SignalEmitter();
		~SignalEmitter();
		
		SignalEmitter & operator=(const SignalEmitter &) = delete;
		SignalEmitter(const SignalEmitter&) = delete;
		void call(const string &, const shared_ptr<Data> &b);
	public:
		static SignalEmitter* get();
		auto connect(const DataPointerSenderSlot &slot) -> boost::signals2::connection;
		
		friend class CodeExecutor;
	};

}
