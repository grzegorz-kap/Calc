#pragma once
#include "Function.h"
namespace PR
{
	class Log10Function :
		public Function
	{
	public:
		Log10Function();
		~Log10Function();
		virtual shared_ptr<Data> run() override;
	};
}

