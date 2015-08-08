#pragma once
#include "Function.h"

namespace PR
{
	class MpfFunction :
		public Function
	{
	public:
		MpfFunction();
		~MpfFunction();

		virtual shared_ptr<Data> run() override;
	};
}
