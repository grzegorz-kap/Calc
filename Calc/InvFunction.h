#pragma once
#include "Function.h"

namespace PR
{
	class InvFunction :
		public Function
	{
	public:
		InvFunction();
		~InvFunction();
		virtual shared_ptr<Data> run() override;
	};

}
