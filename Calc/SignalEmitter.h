#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include <boost\signals2\signal.hpp>
#include <boost\bind\bind.hpp>

#include <string>
#include <memory>

#include "Data.h"
#include "CalcException.h"

namespace PR
{
	class CodeExecutor;
	class CALC_API SignalEmitter
	{
		typedef boost::signals2::signal < void(const char *, const Data *) > DataPointerSender;
		typedef boost::signals2::signal < void(const char *, int) > ExceptionSender;
		typedef DataPointerSender::slot_type DataPointerSenderSlot;
		typedef ExceptionSender::slot_type ExceptionSenderSlot;
	private:
		DataPointerSender sig_data_pointer;
		ExceptionSender sig_exception;
		static SignalEmitter * instance;
		SignalEmitter();
		~SignalEmitter();
		
		SignalEmitter & operator=(const SignalEmitter &) = delete;
		SignalEmitter(const SignalEmitter&) = delete;

		void call(const string &, const shared_ptr<Data> &b);
		void call(const CalcException &);
	public:
		
		static SignalEmitter* get();
		auto connect_output(const DataPointerSenderSlot &slot) -> boost::signals2::connection;
		auto connect_errors(const ExceptionSenderSlot &slot)->boost::signals2::connection;
		
		friend class CodeExecutor;
	};

}
