#pragma once
#include "Function.h"

namespace PR
{
	class Log2Function : public Function
	{
	public:
		Log2Function();
		~Log2Function();
		virtual shared_ptr<Data> run() override;
	};

	class Log10Function : public Function
	{
	public:
		Log10Function();
		~Log10Function();
		virtual shared_ptr<Data> run() override;
	};

	class LogFunction : public Function
	{
	public:
		LogFunction();
		~LogFunction();

		virtual shared_ptr<Data> run() override;
	};

	class SqrtFunction : public Function
	{
	public:
		SqrtFunction();
		~SqrtFunction();
		virtual shared_ptr<Data> run() override;
	};
}