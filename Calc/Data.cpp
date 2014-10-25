#include "stdafx.h"
#include "Data.h"


namespace PR
{
	decltype(Data::TYPE_MAP) Data::TYPE_MAP =
	{
		{ typeid(Matrix<double>),TYPE::M_DOUBLE },
		{ typeid(ComplexNumber<double>),TYPE::DOUBLE }
	};

	decltype(Data::TYPE_NAME_MAP) Data::TYPE_NAME_MAP =
	{
		{ TYPE::M_DOUBLE, "Matrix<double>" },
		{ TYPE::DOUBLE, "double" },
		{ TYPE::OUTPUT, "'function output'" },
		{ TYPE::UNKNOWN, "'unknown'" },
		{ TYPE::TOKEN, "'token'" }
	};

	Data::Data()
	{
	}

	Data::~Data()
	{
	}

	TYPE Data::find_type(const std::type_index &idx)
	{
		auto result = TYPE_MAP.find(idx);
		if (result != TYPE_MAP.end())
			return result->second;
		else
			return TYPE::UNKNOWN;
	}

	const string & Data::find_name(const TYPE &type)
	{
		return TYPE_NAME_MAP.find(type)->second;
	}
}