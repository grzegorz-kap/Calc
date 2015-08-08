#pragma once
#include "Function.h"

namespace KLab
{
	class CosFun : public Function
	{
	public:
		CosFun();
		~CosFun();
		virtual shared_ptr<Data> run() override;
	};

	class SinFun : public Function
	{
	public:
		SinFun();
		~SinFun();
		virtual shared_ptr<Data> run() override;
	};

	class TanFun : public Function
	{
	public:
		TanFun();
		~TanFun();
		virtual shared_ptr<Data> run() override;
	};

	class CotanFun : public Function
	{
	public:
		CotanFun();
		~CotanFun();
		virtual shared_ptr<Data> run() override;
	};
}