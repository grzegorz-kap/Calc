#pragma once
#include "Function.h"
namespace KLab
{
	//! Klasa wywolujaca dzielenie modulo
	class ModFunction :
		public Function
	{
	public:
		ModFunction();
		~ModFunction();

		virtual shared_ptr<Data> run() override;
	};
}
