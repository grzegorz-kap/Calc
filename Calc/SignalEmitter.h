#pragma once
#include "export.h"
#define _SCL_SECURE_NO_WARNINGS

#include <boost\signals2\signal.hpp>
#include <boost\bind\bind.hpp>

#include <string>
#include <memory>

#include "Data.h"
#include "CalcException.h"

namespace PR
{
	class CALC_API SignalEmitter
	{
		typedef boost::signals2::signal < void(const char *, const Data *) > DataPointerSender;
		typedef boost::signals2::signal < void(const char *, int) > ExceptionSender;
		typedef boost::signals2::signal < void() > StopComputingSender;
		
		typedef DataPointerSender::slot_type DataPointerSenderSlot;
		typedef ExceptionSender::slot_type ExceptionSenderSlot;
		typedef StopComputingSender::slot_type StopComputingSlot;

	private:
		DataPointerSender sig_data_pointer;
		ExceptionSender sig_exception;
		StopComputingSender sig_stop_computing;

		static SignalEmitter * instance;
		SignalEmitter();
		~SignalEmitter();
		
		SignalEmitter & operator=(const SignalEmitter &) = delete;
		SignalEmitter(const SignalEmitter&) = delete;

		
	public:
		static SignalEmitter* get();
		
		auto connect_output(const DataPointerSenderSlot &slot) -> boost::signals2::connection;
		auto connect_errors(const ExceptionSenderSlot &slot)->boost::signals2::connection;
		auto connect_stop_computing(const StopComputingSlot &slot)->boost::signals2::connection;

		void call(const string &, const shared_ptr<Data> &b);
		void call(const CalcException &);
		void call_stop();
	};

}
