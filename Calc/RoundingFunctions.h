#pragma once
#include "Function.h"

namespace PR
{
	class CeilFunction : public Function
	{
	public:
		CeilFunction();
		~CeilFunction();
		virtual shared_ptr<Data> run() override;
	};


	class FixFunction : public Function
	{
	public:
		FixFunction();
		~FixFunction();
		virtual shared_ptr<Data> run() override;
	};

	class FloorFunction : public Function
	{
	public:
		FloorFunction();
		~FloorFunction();

		virtual shared_ptr<Data> run() override;
	};

	class RoundFunction : public Function
	{
	public:
		RoundFunction();
		~RoundFunction();

		virtual shared_ptr<Data> run() override;
	};
}