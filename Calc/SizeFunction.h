#pragma once

#include "Function.h"
#include "MatrixBuilder.h"

namespace KLab
{
	class SizeFunction : public Function
	{
	public:
		SizeFunction();
		~SizeFunction();

		virtual shared_ptr<Data> run() override;
	};

	class LengthFunction : public Function
	{
	public:
		LengthFunction();
		~LengthFunction();
		virtual shared_ptr<Data> run() override;
	};

	class NumelFunction : public Function
	{
	public:
		NumelFunction();
		~NumelFunction();
		virtual shared_ptr<Data> run() override;
	};

	class IsColumnFunction : public Function
	{
	public:
		IsColumnFunction();
		~IsColumnFunction();
		virtual shared_ptr<Data> run() override;
	};

	class IsEmptyFunction : public Function
	{
	public:
		IsEmptyFunction();
		~IsEmptyFunction();
		virtual shared_ptr<Data> run() override;
	};

	class IsRowFunction : public Function
	{
	public:
		IsRowFunction();
		~IsRowFunction();
		virtual shared_ptr<Data> run() override;
	};

	class IsScalarFunction : public Function
	{
	public:
		IsScalarFunction();
		~IsScalarFunction();
		virtual shared_ptr<Data> run() override;
	};

	class IsVectorFunction : public Function
	{
	public:
		IsVectorFunction();
		~IsVectorFunction();
		virtual shared_ptr<Data> run() override;
	};

	class ColsFunction : public Function
	{
	public:
		ColsFunction();
		~ColsFunction();
		virtual shared_ptr<Data> run() override;
	};

	class RowsFunction : public Function
	{
	public:
		RowsFunction();
		~RowsFunction();
		virtual shared_ptr<Data> run() override;
	};
}
