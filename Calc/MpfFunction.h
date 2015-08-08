#pragma once
#include "Function.h"

namespace KLab
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
