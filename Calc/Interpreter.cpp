#include "stdafx.h"
#include "Interpreter.h"

#include "SNumber.h"

namespace PR
{
	Interpreter::Interpreter()
	{		
		if (Data::TYPE_MAP_BUILDED == false)
		{
			Data::TYPE_MAP_BUILDED = true;
			Data::TYPE_MAP[typeid(Matrix<int>)] = TYPE::M_INT;
			Data::TYPE_MAP[typeid(Matrix<float>)] = TYPE::M_FLOAT;
			Data::TYPE_MAP[typeid(Matrix<double>)] = TYPE::M_DOUBLE;
			Data::TYPE_MAP[typeid(Value<int>)] = TYPE::INT;
			Data::TYPE_MAP[typeid(Value<float>)] = TYPE::FLOAT;
			Data::TYPE_MAP[typeid(Value<double>)] = TYPE::DOUBLE;
		}
	}

	Interpreter::~Interpreter()
	{
	}


	void Interpreter::work(const string &command)
	{
		
	}

	void Interpreter::workFromFile(const string &fileName)
	{
	}
}