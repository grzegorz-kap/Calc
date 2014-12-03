#pragma once
#include "Function.h"
#include "MatrixBuilder.h"

namespace PR
{
	class RandFunction : public Function
	{
		static bool random_generator_initiated;
	public:
		RandFunction();
		~RandFunction();
		virtual shared_ptr<Data> run() override;
	private:
		void init_rand_generator();
	};


	class OnesFunction : public Function
	{
	public:
		OnesFunction();
		~OnesFunction();
		virtual shared_ptr<Data> run() override;
	};


	class EyeFunction : public Function
	{
	public:
		EyeFunction();
		~EyeFunction();
		virtual shared_ptr<Data> run() override;
	};
}
