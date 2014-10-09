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

	string Interpreter::work(const string &command)
	{
		string temp="";
		string temp2 = "";


		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();
		
		CodeGenerator code(command);
		while (!code.eof()) 
		{
			CodeExecutor exec;
			auto temp3 = exec.run(*code.getInstruction());
			code.inc();
			temp2 += temp3->toString()+ "\n=========================";
		}
			
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> time = end - start;
		temp.append("\nTime: " + std::to_string(time.count()));

		return temp2;
	}

	string Interpreter::workFromFile(const string &fileName)
	{
		std::ifstream file(fileName, std::ios::in|std::ios::binary);

		if (file.is_open())
		{
			std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			str=work(str);
			return str;
		}
		else
			throw CalcException("Can not open file: '" + fileName + "'");
	}
}