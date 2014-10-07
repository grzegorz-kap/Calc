#include "stdafx.h"
#include "Interpreter.h"

#include "CodeGenerator.h"
#include "Value.h"
#include "ComplexNumber.h"

namespace PR
{
	Interpreter::Interpreter()
	{		
	}

	Interpreter::~Interpreter()
	{
	}

	void dupa1(string &str)
	{
		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();

		Matrix<double> AA(1,1,ComplexNumber<double>(10.0));
		Matrix<double> BB(1, 1, ComplexNumber<double>(10.0));

		int i = 10000;
		while (i--)
		{
			

			auto temp3 = AA + BB;
		}

		end = std::chrono::system_clock::now();
		std::chrono::duration<double> time = end - start;
		str.append("\nTime dupa1: " + std::to_string(time.count()));
	}

	void dupa2(string &str)
	{
		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();

		Numeric<Value<double>> *A = new Value<double>(11.5);
		Numeric<Value<double>> *B = new Value<double>(3);

		int i = 10000;
		while (i--)
		{

			
			auto temp2 = *A + B;
		}

		delete A;
		delete B;
		
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> time = end - start;
		str.append("\nTime dupa2: " + std::to_string(time.count()));
	}

	string Interpreter::work(const string &command)
	{
		string temp="";
		string temp2 = "";

		int i = 10;
		while (i--)
		{
			dupa1(temp2);
			dupa2(temp2);
		}

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