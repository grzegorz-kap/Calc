#include "stdafx.h"
#include "Interpreter.h"

#include "Value.h"
#include "Numeric.h"


namespace PR
{
	Interpreter::Interpreter()
	{		
	}

	Interpreter::~Interpreter()
	{
	}


	string Interpreter::work(const string &command)
	{
		string temp="";
		string temp2 = "";

		unique_ptr<Data> a = make_unique<Value<double>>(3.4);
		unique_ptr<Data> b = make_unique<Value<double>>(3.4);
		auto temp12 = *a + b;

		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();
		
		/*CodeGenerator code(command);
		while (!code.eof())
		{
			CodeExecutor exec;
			auto temp3 = exec.run(*code.getInstruction());
			code.inc();
			temp2 += temp3->toString()+ "\n=========================";
		}*/
			
		
	
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