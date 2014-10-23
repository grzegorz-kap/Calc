#pragma once

#include "Function.h"
#include "MatrixBuilder.h"

namespace PR
{
	class SizeFunction : public Function
	{
	public:
		SizeFunction();
		~SizeFunction();

		virtual shared_ptr<Data> run() override;
	};
}

