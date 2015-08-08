#pragma once
#include "Function.h"

namespace PR
{
	class DetFunction : public Function
	{
	public:
		DetFunction();
		~DetFunction();
		virtual shared_ptr<Data> run() override;
	};

	class UrlFunction : public Function
	{
	public:
		UrlFunction();
		~UrlFunction();
		virtual shared_ptr<Data> run() override;
	};

	class InvFunction : public Function
	{
	public:
		InvFunction();
		~InvFunction();
		virtual shared_ptr<Data> run() override;
	};

	class LuFunction : public Function
	{
	public:
		LuFunction();
		~LuFunction();
		virtual shared_ptr<Data> run() override;
	};

	class ConjFunction : public Function
	{
	public:
		ConjFunction();
		~ConjFunction();
		virtual shared_ptr<Data> run() override;
	};
}