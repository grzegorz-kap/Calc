#include "stdafx.h"
#include "IMatrixBuilder.h"


namespace PR
{
	decltype(IMatrixBuilder::TYPES) IMatrixBuilder::TYPES =
	{
		{TYPE::INT,TYPE::M_INT},
		{TYPE::DOUBLE,TYPE::M_DOUBLE},
		{TYPE::FLOAT,TYPE::M_FLOAT},
		{TYPE::C_FLOAT,TYPE::CM_FLOAT},
		{TYPE::C_DOUBLE,TYPE::CM_DOUBLE},
		{TYPE::C_INT,TYPE::CM_INT},
		{ TYPE::M_INT, TYPE::M_INT },
		{TYPE::M_DOUBLE,TYPE::M_DOUBLE},
		{TYPE::M_FLOAT,TYPE::M_FLOAT},
		{TYPE::CM_DOUBLE,TYPE::CM_DOUBLE},
		{ TYPE::CM_FLOAT,TYPE::CM_FLOAT },
		{TYPE::CM_INT,TYPE::CM_INT}
	};


	IMatrixBuilder::IMatrixBuilder()
	{
	}


	IMatrixBuilder::~IMatrixBuilder()
	{
	}
}
