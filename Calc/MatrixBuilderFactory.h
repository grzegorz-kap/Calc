#pragma once

#include "MatrixBuilder.h"

namespace PR
{
	class MatrixBuilderFactory
	{
	public:
		MatrixBuilderFactory()=delete;
		~MatrixBuilderFactory()=delete;

		static unique_ptr<IMatrixBuilder> get(TYPE _type);
	};

}
