#include "stdafx.h"
#include "MpfFunction.h"
#include "TypePromotor.h"

namespace PR
{
	MpfFunction::MpfFunction()
	{
		max_args_count = min_args_count = 1;
		name = "mpf_float";
	}

	MpfFunction::~MpfFunction()
	{
	}

	shared_ptr<Data> MpfFunction::run()
	{
		TYPE type = arguments[0]->_type;
		if (type == TYPE::RM_DOUBLE || type == TYPE::R_DOUBLE)
			return std::move(arguments[0]);
		if (type == TYPE::DOUBLE)
		{
			TypePromotor::convertTo(TYPE::R_DOUBLE, arguments[0], arguments[0]);
		}
		if (type == TYPE::M_DOUBLE)
		{
			TypePromotor::convertTo(TYPE::RM_DOUBLE, arguments[0], arguments[0]);
		}
		return std::move(arguments[0]);
	}
}