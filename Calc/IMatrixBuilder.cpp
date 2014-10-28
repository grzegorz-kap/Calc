#include "stdafx.h"
#include "IMatrixBuilder.h"


namespace PR
{
	decltype(IMatrixBuilder::TYPES) IMatrixBuilder::TYPES =
	{	
		{TYPE::DOUBLE,TYPE::M_DOUBLE},
		{TYPE::M_DOUBLE,TYPE::M_DOUBLE},
		{TYPE::R_DOUBLE,TYPE::RM_DOUBLE},
		{TYPE::RM_DOUBLE,TYPE::RM_DOUBLE}
	};


	IMatrixBuilder::IMatrixBuilder()
	{
	}


	IMatrixBuilder::~IMatrixBuilder()
	{
	}
}
