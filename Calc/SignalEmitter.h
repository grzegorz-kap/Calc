#pragma once
#include "export.h"
#define _SCL_SECURE_NO_WARNINGS

#include <boost\signals2\signal.hpp>
#include <boost\bind\bind.hpp>

#include <string>
#include <memory>

#include "Data.h"
#include "CalcException.h"
#include "VariableInfo.h"

namespace PR
{
	class CALC_API SignalEmitter
	{
		typedef boost::signals2::signal < void(const char *, const Data *) > DataValueSender;
		typedef boost::signals2::signal < void(const char *, int) > ExceptionSender;
		typedef boost::signals2::signal < void() > StopComputingSender;
		typedef boost::signals2::signal < void(const VariableInfo *, int)> AddedVariablesSender;
		typedef boost::signals2::signal < void(vector<string>)> StringSender;
		typedef boost::signals2::signal < void(void)> VoidSender;
		
		typedef DataValueSender::slot_type DataPointerSenderSlot;
		typedef ExceptionSender::slot_type ExceptionSenderSlot;
		typedef StopComputingSender::slot_type StopComputingSlot;
		typedef AddedVariablesSender::slot_type AddedVariablesSlot;
		typedef StringSender::slot_type StringSenderSlot;
		typedef VoidSender::slot_type VoidSenderSlot;

		DataValueSender			*sig_data_value;
		ExceptionSender			*sig_exception;
		StopComputingSender		*sig_stop_computing;
		AddedVariablesSender	*sig_added_variables;
		AddedVariablesSender	*sig_updated_variables;
		StringSender		*sig_removed_variables;
		VoidSender				*sig_execution_complate;
		VoidSender				*sig_clean_screen;

		static SignalEmitter * instance;
		SignalEmitter();
		~SignalEmitter();
		
		SignalEmitter & operator=(const SignalEmitter &) = delete;
		SignalEmitter(const SignalEmitter&) = delete;
	
	public:
		static SignalEmitter* get();
		
		void connect_execution_complate(const VoidSenderSlot &slot);
		void connect_output(const DataPointerSenderSlot &slot);
		void connect_errors(const ExceptionSenderSlot &slot);
		void connect_stop_computing(const StopComputingSlot &slot);
		void connect_added_variables_slot(const AddedVariablesSlot &slot);
		void connect_updated_variables_slot(const AddedVariablesSlot &slot);
		void connect_removed_variables_slot(const StringSenderSlot &slot);
		void connect_clear_screen(const VoidSenderSlot &slot);

		void call_execution_complate();
		void call(const string &, const shared_ptr<Data> &b);
		void call(const CalcException &);
		void call_stop();
		void call_sig_added_variables(const VariableInfo *data, int num);
		void call_sig_updated_variables(const VariableInfo *data, int num);
		void call_sig_removed_variables(vector<string> &removed);
		void call_sig_clear_screen();
	};

}
